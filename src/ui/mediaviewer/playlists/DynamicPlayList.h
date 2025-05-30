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
#ifndef __DYNAMICPLAYLIST_H__
#define __DYNAMICPLAYLIST_H__

#include "RatingCtrl.h"

#include <wx/dynarray.h>
#include <wx/arrimpl.cpp>
#include <wx/string.h>
#include <wx/listbox.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/stattext.h>
#include <wx/choice.h>
#include <wx/textctrl.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/bmpbuttn.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/checkbox.h>
#include <wx/spinctrl.h>
#include <wx/dialog.h>

namespace Guayadeque {

enum guDYNAMIC_FILTER_TYPE {
    guDYNAMIC_FILTER_TYPE_TITLE = 0,
    guDYNAMIC_FILTER_TYPE_ARTIST,
    guDYNAMIC_FILTER_TYPE_ALBUMARTIST,
    guDYNAMIC_FILTER_TYPE_ALBUM,
    guDYNAMIC_FILTER_TYPE_GENRE,
    guDYNAMIC_FILTER_TYPE_LABEL,
    guDYNAMIC_FILTER_TYPE_COMPOSER,
    guDYNAMIC_FILTER_TYPE_COMMENT,
    guDYNAMIC_FILTER_TYPE_PATH,
    guDYNAMIC_FILTER_TYPE_YEAR,
    guDYNAMIC_FILTER_TYPE_RATING,
    guDYNAMIC_FILTER_TYPE_LENGTH,
    guDYNAMIC_FILTER_TYPE_PLAYCOUNT,
    guDYNAMIC_FILTER_TYPE_LASTPLAY,
    guDYNAMIC_FILTER_TYPE_ADDEDDATE,
    guDYNAMIC_FILTER_TYPE_TRACKNUMBER,
    guDYNAMIC_FILTER_TYPE_BITRATE,
    guDYNAMIC_FILTER_TYPE_SIZE,
    guDYNAMIC_FILTER_TYPE_DISK,
    guDYNAMIC_FILTER_TYPE_HASARTWORK
};

enum guDYNAMIC_FILTER_ORDER {
    guDYNAMIC_FILTER_ORDER_TITLE = 0,
    guDYNAMIC_FILTER_ORDER_ARTIST,
    guDYNAMIC_FILTER_ORDER_ALBUMARTIST,
    guDYNAMIC_FILTER_ORDER_ALBUM,
    guDYNAMIC_FILTER_ORDER_GENRE,
    guDYNAMIC_FILTER_ORDER_LABEL,
    guDYNAMIC_FILTER_ORDER_COMPOSER,
    //guDYNAMIC_FILTER_ORDER_PATH,
    guDYNAMIC_FILTER_ORDER_YEAR,
    guDYNAMIC_FILTER_ORDER_RATING,
    guDYNAMIC_FILTER_ORDER_LENGTH,
    guDYNAMIC_FILTER_ORDER_PLAYCOUNT,
    guDYNAMIC_FILTER_ORDER_LASTPLAY,
    guDYNAMIC_FILTER_ORDER_ADDEDDATE,
    guDYNAMIC_FILTER_ORDER_RANDOM
};

enum guDYNAMIC_FILTER_OPTION_STRING {
    guDYNAMIC_FILTER_OPTION_STRING_CONTAINS = 0,
    guDYNAMIC_FILTER_OPTION_STRING_NOT_CONTAINS,
    guDYNAMIC_FILTER_OPTION_STRING_IS,
    guDYNAMIC_FILTER_OPTION_STRING_ISNOT,
    guDYNAMIC_FILTER_OPTION_STRING_START_WITH,
    guDYNAMIC_FILTER_OPTION_STRING_ENDS_WITH
};

enum guDYNAMIC_FILTER_OPTION_LABELS {
    guDYNAMIC_FILTER_OPTION_LABELS_CONTAINS = 0,
    guDYNAMIC_FILTER_OPTION_LABELS_NOT_CONTAINS,
    guDYNAMIC_FILTER_OPTION_LABELS_IS,
    guDYNAMIC_FILTER_OPTION_LABELS_ISNOT,
    guDYNAMIC_FILTER_OPTION_LABELS_START_WITH,
    guDYNAMIC_FILTER_OPTION_LABELS_ENDS_WITH,
    guDYNAMIC_FILTER_OPTION_LABELS_NOTSET
};

enum guDYNAMIC_FILTER_OPTION_YEAR {
    guDYNAMIC_FILTER_OPTION_YEAR_IS = 0,
    guDYNAMIC_FILTER_OPTION_YEAR_ISNOT,
    guDYNAMIC_FILTER_OPTION_YEAR_AFTER,
    guDYNAMIC_FILTER_OPTION_YEAR_BEFORE
};

enum guDYNAMIC_FILTER_OPTION_NUMERIC {
    guDYNAMIC_FILTER_OPTION_NUMERIC_IS = 0,
    guDYNAMIC_FILTER_OPTION_NUMERIC_ISNOT,
    guDYNAMIC_FILTER_OPTION_NUMERIC_AT_LEAST,
    guDYNAMIC_FILTER_OPTION_NUMERIC_AT_MOST
};

enum guDYNAMIC_FILTER_OPTION_DATE {
    guDYNAMIC_FILTER_OPTION_DATE_IN_THE_LAST = 0,
    guDYNAMIC_FILTER_OPTION_DATE_BEFORE_THE_LAST
};

enum guDYNAMIC_FILTER_OPTION_BOOL {
    guDYNAMIC_FILTER_OPTION_BOOL_FALSE = 0,
    guDYNAMIC_FILTER_OPTION_BOOL_TRUE
};

enum guDYNAMIC_FILTER_LIMIT {
    guDYNAMIC_FILTER_LIMIT_TRACKS = 0,
    guDYNAMIC_FILTER_LIMIT_MINUTES,
    guDYNAMIC_FILTER_LIMIT_MEGABYTES,
    guDYNAMIC_FILTER_LIMIT_GIGABYTES
};


// -------------------------------------------------------------------------------- //
class guFilterItem
{
  public :
    int         m_Type;
    int         m_Option;
    wxString    m_Text;
    int         m_Number;
    int         m_Option2;
    wxString    m_Label;

    guFilterItem() { m_Type = 0; }
    ~guFilterItem() {}
    void        Set( int type, int option, const wxString &text );
    void        Set( int type, int option, int number, int option2 );
    wxString    GetLabel( void ) { return m_Label; }
    void        SetFilterLabel( void );

};
WX_DECLARE_OBJARRAY(guFilterItem, guFilterItemArray);

// -------------------------------------------------------------------------------- //
class guDynPlayList
{
  public :
    int                 m_Id;
    wxString            m_Name;
    guFilterItemArray   m_Filters;
    bool                m_Limited;
    int                 m_LimitValue;
    int                 m_LimitType;
    bool                m_Sorted;
    int                 m_SortType;
    bool                m_SortDesc;
    bool                m_AnyOption;

    guDynPlayList() { m_Id = 0; m_Limited = false; m_LimitValue = 0; m_LimitType = 0;
                      m_Sorted = false; m_SortType = 0; m_SortDesc = false; m_AnyOption = false; };
    ~guDynPlayList() {}

    wxString            ToString( void );
    void                FromString( const wxString &playlist );
    bool                IsEmpty( void ) { return m_Filters.IsEmpty(); }
};
WX_DECLARE_OBJARRAY(guDynPlayList, guDynPlayListArray);

// -------------------------------------------------------------------------------- //
class guDynPlayListEditor : public wxDialog
{
	private:

	protected:
        guDynPlayList *     m_PlayList;
        guFilterItemArray * m_Filters;
        int                 m_CurFilter;
        bool                m_HasChanged;
        bool                m_AlbumFilter;

        wxTextCtrl *        m_NameTextCtrl;
		wxListBox *         m_FiltersListBox;
		wxChoice *          m_FilterFieldChoice;
		wxChoice *          m_FilterTextOptionChoice;
		wxChoice *          m_FilterLabelOptionChoice;
		wxTextCtrl *        m_FilterText;
		guRating *          m_FilterRating;
		wxChoice *          m_FilterDateOption2Choice;
		wxSpinCtrl *        m_LengthHours;
		wxStaticText *      m_LengthSeparator1;
		wxSpinCtrl *        m_LengthMinutes;
		wxStaticText *      m_LengthSeparator2;
		wxSpinCtrl *        m_LengthSeconds;
        wxBoxSizer *        m_FilterEditSizer;
		wxBitmapButton *    m_FilterAdd;
		wxBitmapButton *    m_FilterDel;
		wxBitmapButton *    m_FilterAccept;
		wxCheckBox *        m_LimitCheckBox;
		wxSpinCtrl *        m_LimitSpinCtrl;
		wxChoice *          m_LimitChoice;
		wxCheckBox *        m_SortCheckBox;
		wxChoice *          m_SortChoice;
		wxCheckBox *        m_DescCheckBox;

		wxCheckBox *        m_AddOnAnyCheckBox;

		wxButton *          m_BtnOk;

		// event handlers, overide them in your derived class
		void                OnFiltersSelected( wxCommandEvent &event );
		void                OnFilterFieldSelected( wxCommandEvent& event );
		void                OnFilterOptionSelected( wxCommandEvent& event );
		void                OnFilterTextChanged( wxCommandEvent& event );
        void                OnFilterDateOption2Selected( wxCommandEvent &event );
		void                OnFilterAddClicked( wxCommandEvent& event );
		void                OnFilterDelClicked( wxCommandEvent& event );
		void                OnFilterUpdateClicked( wxCommandEvent& event );
		void                OnLimitChecked( wxCommandEvent& event );
		void                OnSortChecked( wxCommandEvent& event );
		void                OnRatingChanged( guRatingEvent &event );
		void                OnNameChanged( wxCommandEvent &event );
		void                OnHoursChanged( wxSpinEvent &event );
		void                OnMinutesChanged( wxSpinEvent &event );
		void                OnSecondsChanged( wxSpinEvent &event );

		bool                FilterHasChanged( void );
		guFilterItem        GetFilterItem( void );
		void                UpdateEditor( int FilterType );


	public:
		guDynPlayListEditor( wxWindow * parent, guDynPlayList * playlist, const bool albumfilter = false );
		~guDynPlayListEditor();

		void                FillPlayListEditData( void );

};

}

#endif
// -------------------------------------------------------------------------------- //
