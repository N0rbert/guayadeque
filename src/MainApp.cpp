/*
   Copyright (C) 2008-2023 J.Rios <anonbeat@gmail.com>
   Copyright (C) 2024-2025 Tiago T Barrionuevo <thothix@protonmail.com>

   This file is part of Guayadeque Music Player.

   Guayadeque is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   Guayadeque is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with Guayadeque. If not, see <https://www.gnu.org/licenses/>.
*/
#include "MainApp.h"

#include "Config.h"
#include "Curl.h"
#include "Images.h"
#include "MainFrame.h"
#include "mpris.h"
#include "SplashWin.h"
#include "Settings.h"
#include "Utils.h"

#include "wx/clipbrd.h"
#include <wx/image.h>
#include <wx/tooltip.h>
#include <wx/stdpaths.h>
#include <wx/utils.h>

#include <wx/debugrpt.h>

IMPLEMENT_APP( Guayadeque::guMainApp );

namespace Guayadeque {

// -------------------------------------------------------------------------------- //
guMainApp::guMainApp() : wxApp()
{
    m_DbCache = nullptr;
    m_SingleInstanceChecker = nullptr;

#if wxUSE_ON_FATAL_EXCEPTION    // Thanks TheBigRed
    wxHandleFatalExceptions();
#endif

    if (!wxDirExists(guPATH_CONFIG))
    {
        wxMkdir(guPATH_CONFIG, 0770);
        guLogMessage(wxT("Created the configuration folder"));
    }

    if (!wxDirExists(guPATH_COLLECTIONS))
    {
        wxMkdir(guPATH_COLLECTIONS, 0770);
        guLogMessage(wxT("Created the collections folder"));
    }

    if (!wxDirExists(guPATH_RADIOS))
    {
        wxMkdir(guPATH_RADIOS, 0770);
        guLogMessage(wxT("Created the Radios folder"));
    }

    if (!wxDirExists(guPATH_MAGNATUNE))
    {
        wxMkdir(guPATH_MAGNATUNE, 0770);
        wxMkdir(guPATH_MAGNATUNE_COVERS, 0770);
        guLogMessage(wxT("Created the Magnatune folder"));
    }

    if (!wxDirExists(guPATH_PODCASTS))
    {
        wxMkdir(guPATH_PODCASTS, 0770);
        guLogMessage(wxT("Created the Podcasts folder"));
    }

    if (!wxDirExists(guPATH_DEVICES))
    {
        wxMkdir(guPATH_DEVICES, 0770);
        guLogMessage(wxT("Created the Devices folder"));
    }

    if (!wxDirExists(guPATH_LAYOUTS))
    {
        wxMkdir(guPATH_LAYOUTS, 0770);
        guLogMessage(wxT("Created the Layouts folder"));
    }

    if (!wxFileExists(guPATH_CONFIG_FILENAME))
    {
        if (wxFileExists(wxT(DATADIR "/guayadeque.default.conf")))
            wxCopyFile(wxT(DATADIR "/guayadeque.default.conf"),
                       guPATH_CONFIG_FILENAME, false);

        guLogMessage(wxT("Created the default configuration file"));
    }

    if (!wxFileExists(guPATH_EQUALIZERS_FILENAME))
    {
        if (wxFileExists(wxT(DATADIR "/equalizers.default.conf")))
            wxCopyFile(wxT(DATADIR "/equalizers.default.conf"),
                       guPATH_EQUALIZERS_FILENAME, false);
        guLogMessage(wxT("Created the default equalizers file"));
    }

    if (!wxFileExists(guPATH_LYRICS_SOURCES_FILENAME))
    {
        if (wxFileExists(wxT(DATADIR "/lyrics_sources.xml")))
            wxCopyFile(wxT(DATADIR "/lyrics_sources.xml"),
                       guPATH_LYRICS_SOURCES_FILENAME, false);
        guLogMessage(wxT("Created the default lyrics sources file"));
    }

    m_Config = new guConfig();
    m_Config->Set(m_Config);

    checkDesktopConfig();
}

// -------------------------------------------------------------------------------- //
guMainApp::~guMainApp()
{
    if (m_SingleInstanceChecker)
        delete m_SingleInstanceChecker;

    if (m_DbCache)
    {
        m_DbCache->Close();
        delete m_DbCache;
    }

    if (m_Config)
        delete m_Config;
}

// -------------------------------------------------------------------------------- //
void guMainApp::checkDesktopConfig()
{
    wxString xdg_current_desktop = std::getenv("XDG_CURRENT_DESKTOP");

    guLogMessage( wxT("XDG Current Desktop: %s"), xdg_current_desktop);
    xdg_current_desktop = xdg_current_desktop.Lower();

    // Get the preferences desktop
    wxString preference_desktop = m_Config->ReadStr(CONFIG_KEY_GENERAL_DESKTOP, m_desktop, CONFIG_PATH_GENERAL);

    // Get the actual desktop
    if (xdg_current_desktop.Contains("kde") || xdg_current_desktop.Contains("plasma"))
        m_desktop = "kde";
    else if (xdg_current_desktop.Contains("xfce"))
        m_desktop = "xfce";
    else if (xdg_current_desktop.Contains("lxqt"))
        m_desktop = "lxqt";
    else        // cinnamon, mate, ...
        m_desktop = "gnome";

    if (m_desktop == preference_desktop)
        return;

    m_Config->WriteStr(CONFIG_KEY_GENERAL_DESKTOP, m_desktop, CONFIG_PATH_GENERAL);
    m_Config->Flush();
    guLogMessage( wxT("checkDesktopConfig - Current Desktop Changed to: %s"), m_desktop);

    // Old commands config
    wxArrayString Commands = m_Config->ReadAStr( CONFIG_KEY_COMMANDS_EXEC, wxEmptyString, CONFIG_PATH_COMMANDS_EXECS );
    size_t count = Commands.GetCount();

    // Returns if already converted (no old config)
    //if (!count)
    //    return;

    // Convert from "command/execs" to "command/desktop/execs"
    wxArrayString Names = m_Config->ReadAStr( CONFIG_KEY_COMMANDS_NAME, wxEmptyString, CONFIG_PATH_COMMANDS_NAMES );

    m_Config->DeleteCategory(CONFIG_PATH_COMMANDS_EXECS);
    m_Config->DeleteCategory(CONFIG_PATH_COMMANDS_NAMES);
    m_Config->Flush();

    // Read the current/New default .conf
    auto default_config = new guConfig(wxT(DATADIR "/guayadeque.default.conf"), false);
    wxString ws_desktops[] = guDESKTOP_MANAGERS;
    wxArrayString desktops(WXSIZEOF(ws_desktops), ws_desktops);
    wxArrayString default_cmds;
    bool found;

    for (size_t ix_desktop = 0; ix_desktop < desktops.GetCount(); ix_desktop++)
    {
        wxString category_execs = wxString::Format(CONFIG_PATH_COMMANDS_DESKTOP_EXECS, desktops[ix_desktop]);
        wxString category_names = wxString::Format(CONFIG_PATH_COMMANDS_DESKTOP_NAMES, desktops[ix_desktop]);

        wxArrayString new_cmds = m_Config->ReadAStr(CONFIG_KEY_COMMANDS_EXEC, wxEmptyString, category_execs);
         if (!new_cmds.IsEmpty())
            continue;

        wxArrayString template_cmds = default_config->ReadAStr( CONFIG_KEY_COMMANDS_EXEC, wxEmptyString, category_execs);
        wxArrayString template_names = default_config->ReadAStr( CONFIG_KEY_COMMANDS_NAME, wxEmptyString, category_names);
        if (ix_desktop == 0)
            default_cmds = default_config->ReadAStr( CONFIG_KEY_COMMANDS_EXEC, wxEmptyString, category_execs);

        if (m_desktop == desktops[ix_desktop])
        {
            // Import the current commands to current desktop
            for (size_t ix_cmds = 0; ix_cmds < count; ix_cmds++)
            {
                found = template_cmds.Index(Commands[ix_cmds]) != wxNOT_FOUND;
                if (!found)
                    found = default_cmds.Index(Commands[ix_cmds]) != wxNOT_FOUND;

                if (!found)
                {
                    template_cmds.Insert(Commands[ix_cmds], ix_cmds);
                    template_names.Insert(Names[ix_cmds], ix_cmds);
                }
            }
        }

        m_Config->WriteAStr(CONFIG_KEY_COMMANDS_EXEC, template_cmds, category_execs);
        m_Config->WriteAStr(CONFIG_KEY_COMMANDS_NAME, template_names, category_names);
    }

    m_Config->Flush();
    guLogMessage( wxT("checkDesktopConfig - Commands upgraded to desktop: %s"), m_desktop);
}

// -------------------------------------------------------------------------------- //
// Its done this way to avoid the warning of temporary address
void inline Append_String( DBusMessageIter * iter, const char * str )
{
    dbus_message_iter_append_basic( iter, DBUS_TYPE_STRING, &str );
}

// -------------------------------------------------------------------------------- //
bool SendFilesByMPRIS( const int argc, wxChar * argv[] )
{
    DBusError dberr;
    DBusConnection * dbconn;
    DBusMessage * dbmsg, * dbreply;
    DBusMessageIter dbiter;
    DBusMessageIter dbitertracks;

    dbus_error_init( &dberr );
    dbconn = dbus_bus_get( DBUS_BUS_SESSION, &dberr );

    if( dbus_error_is_set( &dberr ) )
    {
         printf( "getting session bus failed: %s\n", dberr.message );
         dbus_error_free( &dberr );
         return false;
    }

    dbmsg = dbus_message_new_method_call( GUAYADEQUE_MPRIS_SERVICENAME,
                                          GUAYADEQUE_MPRIS_TRACKLIST_PATH,
                                          GUAYADEQUE_MPRIS_INTERFACE,
                                          "AddTracks" );
    if( dbmsg == NULL )
    {
         guLogError( wxT( "Couldn’t create a DBusMessage" ) );
         return false;
    }

    dbus_message_iter_init_append( dbmsg, &dbiter );
    dbus_message_iter_open_container( &dbiter, DBUS_TYPE_ARRAY, "s", &dbitertracks );

    wxString FilePath;
    for( int index = 1; index < argc; index++ )
    {
        FilePath = argv[ index ];
        //guLogMessage( wxT( "Trying to add file '%s'" ), argv[ index ] );

        Append_String( &dbitertracks, FilePath.char_str() );
    }

    dbus_message_iter_close_container( &dbiter, &dbitertracks );

    dbus_bool_t PlayTrack = false;
    dbus_message_iter_append_basic( &dbiter, DBUS_TYPE_BOOLEAN, &PlayTrack );

    dbreply = dbus_connection_send_with_reply_and_block( dbconn, dbmsg, 5000, &dberr );
    if( dbus_error_is_set( &dberr ) )
    {
        guLogMessage( wxT( "Error adding files: '%s'" ), wxString( dberr.message, wxConvUTF8 ).c_str() );
        dbus_message_unref( dbmsg );
        dbus_error_free( &dberr );
        return false;
    }

    if( dbreply )
        dbus_message_unref( dbreply );

    /* Don’t need this anymore */
    dbus_message_unref( dbmsg );

    dbus_connection_unref( dbconn );

    return true;
}

// -------------------------------------------------------------------------------- //
bool MakeWindowVisible( void )
{
    DBusError dberr;
    DBusConnection * dbconn;
    DBusMessage * dbmsg, * dbreply;

    dbus_error_init( &dberr );
    dbconn = dbus_bus_get( DBUS_BUS_SESSION, &dberr );

    if( dbus_error_is_set( &dberr ) )
    {
         printf( "getting session bus failed: %s\n", dberr.message );
         dbus_error_free( &dberr );
         return false;
    }

    dbmsg = dbus_message_new_method_call( "org.mpris.MediaPlayer2.guayadeque",
                                          "/org/mpris/MediaPlayer2",
                                          "org.mpris.MediaPlayer2",
                                          "Raise" );
    if (dbmsg == nullptr)
    {
         guLogError( wxT( "Couldn’t create a DBusMessage" ) );
         return false;
    }

    dbreply = dbus_connection_send_with_reply_and_block( dbconn, dbmsg, 5000, &dberr );
    if( dbus_error_is_set( &dberr ) )
    {
        guLogMessage( wxT( "Error showing window" ) );
        dbus_message_unref( dbmsg );
        dbus_error_free( &dberr );
        return false;
    }

    if( dbreply )
        dbus_message_unref( dbreply );

    /* Don’t need this anymore */
    dbus_message_unref( dbmsg );

    dbus_connection_unref( dbconn );

    return true;
}

// -------------------------------------------------------------------------------- //
bool guMainApp::OnInit()
{
    guRandomInit();

    wxLog::SetActiveTarget( new wxLogStderr( stdout ) );

    // Init all image handlers
    wxInitAllImageHandlers();

    const wxString AppName = wxString::Format( wxT( ".guayadeque/.guayadeque-%s" ), wxGetUserId().c_str() );
    //guLogMessage( wxT( "Init: %s" ), AppName.c_str() );
    while( true )
    {
        if( m_SingleInstanceChecker )
            delete m_SingleInstanceChecker;

        m_SingleInstanceChecker = new wxSingleInstanceChecker( AppName );

        if( m_SingleInstanceChecker->IsAnotherRunning() )
        {
            int RetryCnt = 0;
            if( argc > 1 )
            {
                while( RetryCnt++ < 25 )
                {
                    if( SendFilesByMPRIS( argc, argv ) )
                        break;

                    wxMilliSleep( 100 );
                }
            }

            if( ( RetryCnt < 25 ) && MakeWindowVisible() )
                return false;

            //guLogMessage( wxT( "Another program instance is already running, aborting." ) );
            if( wxMessageBox( _( "Another program instance is already running." ) + "\n" + _( "Do you want to continue with the program?" ),
                             _( "Confirm" ),
                             wxICON_QUESTION | wxYES_NO ) == wxYES )
            {
                if( !wxRemoveFile( wxGetHomeDir() + "/" + AppName ) )
                    guLogMessage( wxT( "Could not delete the file: %s" ), AppName.c_str() );
                wxMilliSleep( 1000 );
            }
            else
            {
                delete m_SingleInstanceChecker;
                return false;
            }
        }
        else
            break;
    }

    // If enabled Show the Splash Screen on Startup
    if( m_Config->ReadBool( CONFIG_KEY_GENERAL_SHOW_SPLASH_SCREEN, true, CONFIG_PATH_GENERAL ) )
    {
        guSplashFrame * SplashFrame = new guSplashFrame( 0 );
        if( !SplashFrame )
            guLogError( wxT( "Could not create splash object" ) );
        SplashFrame->Show( true );
        wxYield();
        //wxMilliSleep( 300 );
    }

    // Use the primary clipboard which is shared with other applications
    wxTheClipboard->UsePrimarySelection( false );

    // Init the Curl Library
    guCurl::CurlInit();

    int LangId = m_Config->ReadNum( CONFIG_KEY_GENERAL_LANGUAGE, wxLANGUAGE_DEFAULT, CONFIG_PATH_GENERAL );
    if( m_Locale.Init( LangId ) )
    {
        m_Locale.AddCatalogLookupPathPrefix( wxT( "/usr/share/locale" ) );
        m_Locale.AddCatalog( wxT( "guayadeque" ) );
        guLogMessage( wxT( "Initialized locale ( %s )" ), m_Locale.GetName().c_str() );
    }
    else
    {
        const wxLanguageInfo * LangInfo = wxLocale::GetLanguageInfo( LangId );
        if( LangInfo )
        {
            guLogError( wxT( "Could not initialize the translations engine for ( %s )" ), LangInfo->CanonicalName.c_str() );
            guLogError( wxT( "Locale directory '%s'" ), wxStandardPaths::Get().GetLocalizedResourcesDir( LangInfo->CanonicalName, wxStandardPaths::ResourceCat_Messages).c_str() );
        }
        else
            guLogError( wxT( "Could not initialize the translations engine for (%d)" ), LangId );
    }

    // Enable tooltips
    wxToolTip::Enable( true );

    m_DbCache = new guDbCache( guPATH_DBCACHE );
    if( !m_DbCache )
        guLogError( wxT( "Could not open the guayadeque cache database" ) );

    m_DbCache->SetDbCache();

    // Initialize the MainFrame object
    guMainFrame * Frame = new guMainFrame( 0, m_DbCache );
    SetTopWindow( Frame );
    //Frame->SetMainFrame();
    wxIcon MainIcon;
    MainIcon.CopyFromBitmap( guImage( guIMAGE_INDEX_guayadeque ) );
    Frame->SetIcon( MainIcon );

    // If Minimize is enabled minimized or hide it if Taskbar Icon is enabled
    if( m_Config->ReadBool( CONFIG_KEY_GENERAL_START_MINIMIZED, false, CONFIG_PATH_GENERAL ) )
    {
        if( m_Config->ReadBool( CONFIG_KEY_GENERAL_SHOW_TASK_BAR_ICON, false, CONFIG_PATH_GENERAL ) &&
            m_Config->ReadBool( CONFIG_KEY_GENERAL_CLOSE_TO_TASKBAR, false, CONFIG_PATH_GENERAL ) )
        {
            Frame->Show( false );
            //Frame->Hide();
        }
        else
        {
            Frame->Show();
            Frame->Iconize( true );
        }
    }
    else
        Frame->Show();

    return true;
}

// -------------------------------------------------------------------------------- //
int guMainApp::OnExit()
{
    // Free any resources used by Curl Library
    guCurl::CurlDone();
    return 0;
}

// -------------------------------------------------------------------------------- //
void guMainApp::OnFatalException()
{
    wxDebugReport Report;
    wxDebugReportPreviewStd Preview;

    Report.AddAll();

    if( Preview.Show( Report ) )
        Report.Process();
}

}
