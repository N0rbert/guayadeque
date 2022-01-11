// -------------------------------------------------------------------------------- //
//    Copyright (C) 2008-2022 J.Rios anonbeat@gmail.com
//
//    This Program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 3, or (at your option)
//    any later version.
//
//    This Program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program; see the file LICENSE.  If not, write to
//    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
//    Boston, MA 02110-1301 USA.
//
//    http://www.gnu.org/copyleft/gpl.html
//
// -------------------------------------------------------------------------------- //
#ifndef __AMAZON_H__
#define __AMAZON_H__

#include "ArrayStringArray.h"
#include "CoverFetcher.h"

#include <wx/xml/xml.h>

namespace Guayadeque {

class guFetchCoverLinksThread;

// -------------------------------------------------------------------------------- //
class guAmazonCoverFetcher : public guCoverFetcher
{
  private :
    wxArrayString   GetImageInfo( wxXmlNode * XmlNode );
    int             ExtractImagesInfo( wxString &content );

  public :
    guAmazonCoverFetcher( guFetchCoverLinksThread * mainthread, guArrayStringArray * coverlinks,
                                    const wxChar * artist, const wxChar * album );
    virtual int   AddCoverLinks( int pagenum );
};

}

#endif
// -------------------------------------------------------------------------------- //
