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
#include "YeListBox.h"

#include "Accelerators.h"
#include "EventCommandIds.h"
#include "Config.h"
#include "Images.h"
#include "OnlineLinks.h"
#include "MainApp.h"
#include "Utils.h"
#include "LibPanel.h"
#include "MediaViewer.h"

namespace Guayadeque {

// -------------------------------------------------------------------------------- //
guYeListBox::guYeListBox( wxWindow * parent, guLibPanel * libpanel, guDbLibrary * db, const wxString &label ) :
             guAccelListBox( parent, db, label )
{
    m_LibPanel = libpanel;

    CreateAcceleratorTable();

    ReloadItems();
};

// -------------------------------------------------------------------------------- //
guYeListBox::~guYeListBox()
{
}

// -------------------------------------------------------------------------------- //
void guYeListBox::CreateAcceleratorTable( void )
{
    wxAcceleratorTable AccelTable;
    wxArrayInt AliasAccelCmds;
    wxArrayInt RealAccelCmds;

    AliasAccelCmds.Add( ID_PLAYER_PLAYLIST_SAVE );
    AliasAccelCmds.Add( ID_PLAYER_PLAYLIST_EDITTRACKS );
    AliasAccelCmds.Add( ID_TRACKS_PLAY );
    AliasAccelCmds.Add( ID_TRACKS_ENQUEUE_AFTER_ALL );
    AliasAccelCmds.Add( ID_TRACKS_ENQUEUE_AFTER_TRACK );
    AliasAccelCmds.Add( ID_TRACKS_ENQUEUE_AFTER_ALBUM );
    AliasAccelCmds.Add( ID_TRACKS_ENQUEUE_AFTER_ARTIST );
    AliasAccelCmds.Add( ID_PLAYER_PLAYLIST_SEARCH );

    RealAccelCmds.Add( ID_YEAR_SAVETOPLAYLIST );
    RealAccelCmds.Add( ID_YEAR_EDITTRACKS );
    RealAccelCmds.Add( ID_YEAR_PLAY );
    RealAccelCmds.Add( ID_YEAR_ENQUEUE_AFTER_ALL );
    RealAccelCmds.Add( ID_YEAR_ENQUEUE_AFTER_TRACK );
    RealAccelCmds.Add( ID_YEAR_ENQUEUE_AFTER_ALBUM );
    RealAccelCmds.Add( ID_YEAR_ENQUEUE_AFTER_ARTIST );
    RealAccelCmds.Add( ID_LIBRARY_SEARCH );

    if( guAccelDoAcceleratorTable( AliasAccelCmds, RealAccelCmds, AccelTable ) )
    {
        SetAcceleratorTable( AccelTable );
    }
}

// -------------------------------------------------------------------------------- //
void guYeListBox::GetItemsList( void )
{
    m_Db->GetYears( m_Items );
}

// -------------------------------------------------------------------------------- //
int guYeListBox::GetSelectedSongs( guTrackArray * songs, const bool isdrag ) const
{
    int Count = m_Db->GetYearsSongs( GetSelectedItems(), songs );
    m_LibPanel->NormalizeTracks( songs, isdrag );
    return Count;
}

// -------------------------------------------------------------------------------- //
void guYeListBox::CreateContextMenu( wxMenu * Menu ) const
{
    wxMenuItem * MenuItem;

    int SelCount = GetSelectedCount();
    int ContextMenuFlags = m_LibPanel->GetContextMenuFlags();

    MenuItem = new wxMenuItem( Menu, ID_YEAR_PLAY,
                            wxString( _( "Play" ) ) + guAccelGetCommandKeyCodeString( ID_TRACKS_PLAY ),
                            _( "Play current selected artists" ) );
    MenuItem->SetBitmap( guImage( guIMAGE_INDEX_player_tiny_light_play ) );
    Menu->Append( MenuItem );
    MenuItem->Enable( SelCount );

    MenuItem = new wxMenuItem( Menu, ID_YEAR_ENQUEUE_AFTER_ALL,
                            wxString( _( "Enqueue" ) ) + guAccelGetCommandKeyCodeString( ID_TRACKS_ENQUEUE_AFTER_ALL ),
                            _( "Add current selected tracks to playlist" ) );
    MenuItem->SetBitmap( guImage( guIMAGE_INDEX_tiny_add ) );
    Menu->Append( MenuItem );
    MenuItem->Enable( SelCount );

    wxMenu * EnqueueMenu = new wxMenu();

    MenuItem = new wxMenuItem( EnqueueMenu, ID_YEAR_ENQUEUE_AFTER_TRACK,
                            wxString( _( "Current Track" ) ) +  guAccelGetCommandKeyCodeString( ID_TRACKS_ENQUEUE_AFTER_TRACK ),
                            _( "Add current selected tracks to playlist after the current track" ) );
    MenuItem->SetBitmap( guImage( guIMAGE_INDEX_tiny_add ) );
    EnqueueMenu->Append( MenuItem );
    MenuItem->Enable( SelCount );

    MenuItem = new wxMenuItem( EnqueueMenu, ID_YEAR_ENQUEUE_AFTER_ALBUM,
                            wxString( _( "Current Album" ) ) +  guAccelGetCommandKeyCodeString( ID_TRACKS_ENQUEUE_AFTER_ALBUM ),
                            _( "Add current selected tracks to playlist after the current album" ) );
    MenuItem->SetBitmap( guImage( guIMAGE_INDEX_tiny_add ) );
    EnqueueMenu->Append( MenuItem );
    MenuItem->Enable( SelCount );

    MenuItem = new wxMenuItem( EnqueueMenu, ID_YEAR_ENQUEUE_AFTER_ARTIST,
                            wxString( _( "Current Artist" ) ) +  guAccelGetCommandKeyCodeString( ID_TRACKS_ENQUEUE_AFTER_ARTIST ),
                            _( "Add current selected tracks to playlist after the current artist" ) );
    MenuItem->SetBitmap( guImage( guIMAGE_INDEX_tiny_add ) );
    EnqueueMenu->Append( MenuItem );
    MenuItem->Enable( SelCount );

    Menu->Append( wxID_ANY, _( "Enqueue After" ), EnqueueMenu );

    if( SelCount )
    {
        if( ContextMenuFlags & guCONTEXTMENU_EDIT_TRACKS )
        {
            Menu->AppendSeparator();

            MenuItem = new wxMenuItem( Menu, ID_YEAR_EDITTRACKS,
                                wxString( _( "Edit Songs" ) ) +  guAccelGetCommandKeyCodeString( ID_PLAYER_PLAYLIST_EDITTRACKS ),
                                _( "Edit the selected tracks" ) );
            MenuItem->SetBitmap( guImage( guIMAGE_INDEX_tiny_edit ) );
            Menu->Append( MenuItem );
        }

        Menu->AppendSeparator();

        MenuItem = new wxMenuItem( Menu, ID_YEAR_SAVETOPLAYLIST,
                                wxString( _( "Save to Playlist" ) ) +  guAccelGetCommandKeyCodeString( ID_PLAYER_PLAYLIST_SAVE ),
                                _( "Save the selected tracks to Playlist" ) );
        MenuItem->SetBitmap( guImage( guIMAGE_INDEX_tiny_doc_save ) );
        Menu->Append( MenuItem );

        if( ContextMenuFlags & guCONTEXTMENU_COPY_TO )
        {
            m_LibPanel->CreateCopyToMenu( Menu );
        }
    }

    m_LibPanel->CreateContextMenu( Menu );
}

// -------------------------------------------------------------------------------- //
wxString guYeListBox::GetSearchText( int item ) const
{
    return GetItemName( item );
}

// -------------------------------------------------------------------------------- //
int guYeListBox::FindYear( const int year )
{
    int Count = m_Items->Count();
    for( int Index = 0; Index < Count; Index++ )
    {
        if( m_Items->Item( Index ).m_Id == year )
        {
            return Index;
        }
    }
    return wxNOT_FOUND;
}

}

// -------------------------------------------------------------------------------- //
