Guayadeque Music Player
=======================

Changelog
=========

0.7.2 (2025-06-07)
------------------
###### Marduk, the cat

### Features
  * Added CoreAudio output device support in preferences (for MacOS).
    Closes #65. Thanks to @barracuda156.

### Enhancements
  * Enhancements in reading some missing cue sheets metadata from the audio file.
  * Make the wx qa component optional (some systems don't support it). Building without
    it will disable the fatal exception report generation. Closes #63.
  * Removed warnings for GCC 15.1.
  * Added gstreamer-plugins-good as a dependency in the INSTALL.md.
  * Added Wiki and Discussions links to the README.md.
  * Updated Greek, Italian, Spanish and Catalan translations. Thanks to @filochard.

### Bugfixes
  * Playlist/queue updates to handle properly playlists with cue sheets and/or tracks
    from multiple collections:
    * Fixed missing updates to playcount and last play date (even if collection is closed).
    * Fixed playlist reload after Guayadeque restart.
  * Some important cue sheets related fixes:
    * Fixed bug in the library scan where sometimes the length of the last track of 
      cue sheets wasn't updating properly.
      * If you have cue sheets, it's recommended that you rescan your collections.
        You can also rescan only the directories containing the cue sheets.
    * Fixed the enqueue of cue sheets getting duplicates and wrong track number and length.
  * Fixed the "Set as Next Track" button in the playlist toolbar to handle properly
    the tracks before the current track (enable them to be set as next track).
  * Fixed build on case-insensitive filesystems causing compilation errors due wrongly
    included headers caused by duplicated headers filenames.
    Closes PR #64. Thanks to @barracuda156.

0.7.1 (2025-05-14)
------------------

### Features
  * Added a "Move here" feature in the File Browser directory tree:
    * Now it's possible to move a directory location without lose the library data
      and statistics. The new "Move here" context menu option moves a previous copied
      directory to the selected target location and updates the library as well.

### Enhancements
  * Adjusted the Podcast Editor dialog size.
  * Added a Find Cover button in the Cover Editor to repeat the cover search
    (same as hit enter in the text controls).
  * Updated French, Portuguese and Brazilian Portuguese translations.

### Bugfixes
  * Fixed the "Paste" context menu option, in the File Browser directory tree,
    to paste the directory instead only the directory content.
  * Fixed the "Rename" context menu option, in the File Browser directory tree, 
    that wasn't refreshing the modified item tree.

0.7.0 (2025-02-22)
------------------

### Enhancements
  * Updated the wiki manual and the Guayadeque Help menu link.

### Bugfixes
  * Fixed a long time bug that causes playback skipping after around 20/30 minutes
    playing a long track or podcast.

### Removed
  * Removed the no more functional Jamendo feature.
  * Removed the build option CXX11_RNG. The srand is now fully replaced by the
    C++11 random number generator.

0.6.5 (2025-02-20)
------------------

### Enhancements
  * Add C++20 compiling compatibility.
  * Updated Croatian translations.

### Bugfixes
  * Fix crash when opening Jamendo and Magnatune sources (introduced in 0.6.0).

0.6.4 (2025-01-25)
------------------

### Bugfixes
  * Fix compatibility with wxWidgets prior to 3.2 (regression from 0.6.2)
  * Fix bug in conversion of preferences commands (introduced in 0.6.2)

0.6.3 (2025-01-24)
------------------

### Features
  * Audio formats support:
    * Added support for DSF files in the library (without tagging support by now).
    * Added back support for AAC files in the library (removed in 0.5.0). 
    Now Guayadeque can:
      * Add AAC and DSF files to the library. 
      * Edit AAC tags through Track Editor, only when using Taglib 2.
        If using Taglib 1, the editor will be disabled for editing.

### Enhancements
  * Library Scan and Edit Cover now can find covers that has the album name
    (by default and as a second option to "Words to detect covers" in collection
    preferences).
  * Select the first collection by default when open Preferences -> Collections
  * Updated Croatian translations. Thanks to Mario (@mtadic). 
  * Updated Catalan translations.

### Bugfixes
  * Added missing Croatian language to preferences.

0.6.2 (2024-12-11)
------------------

### Features
  * Check/set the proper default commands for the current desktop manager.
    Gnome (including compatible DEs like Cinnamon and Mate), KDE, xfce and
    LXQT are currently detected and configured (fallback to Gnome commands).

### Enhancements
  * Lyrics preferences: Change source embedded default to true.
  * "Randomize" playlist feature renamed to "Shuffle".
  * Added a external.pot file to store messages external to the source code
    to enable its translation through merging it into guayadeque.pot.
  * Change the Guayadeque build to update the translations .po files
    automatically (after the .pot generation). This will:
    - Update all .po files with the new messages from .pot file to further 
      translation.
    - Comment out messages in the .po files that aren't in the .pot file anymore.
  * Lots of translation refactorings (all languages).
  * Added translation to source and target lyrics options.
  * Updated French, Greek, Italian, Spanish and Catalan translations. 
    Thanks to filochard.
  * Updated German translations. Thanks to martinkg.
  * Updated Portuguese and Brazilian Portuguese translations.
  * Small UI adjustments (playlist context menu, taskbar menu, preferences).

0.6.1 (2024-11-12)
------------------

### Enhancements
  * Metadata fixes and changes to the current standards:
    * guayadeque.appdata.xml:
      - Renamed to org.guayadeque.guayadeque.metainfo.xml.
      - Destination changed from /usr/share/appdata to /usr/share/metainfo.
      - Updated project_license to use SPDX-License-Identifier.
    * guayadeque.desktop renamed to org.guayadeque.guayadeque.desktop.
    * guayadeque.png destination changed from "pixmaps/" to 
      "icons/hicolor/64x64/apps/"
  * Added RADIOS.md for radios related information.
  * Added missing license headers.
  * Small UI adjustments (songs editor).

### Removed
  * Removed deprecated collection database index.

0.6.0 (2024-10-25)
------------------

### Features
  * Added a new Directory Panel in the Collections/Library
    - Now it's possible to navigate throughout the collection's directories tree
      while filtering the corresponding Genres, Artists, Albums, Songs and so on.
    - It also restricts the search to the selected directory meanwhile it updates
      the search if the directory is changed.
    - The panel can be shown/hidden in Sources -> "Collection Name" -> Library ->
      Directories menu item.
  * Added option in Preferences -> General to hide the player album cover. It's
    useful if you already have the cover panel visible and make more room to the
    player information.

### Enhancements
  * Added collate accents on media search. The search function now make use of
    Unicode Collation to match accented characters.
  * Preload the current track in the player at startup and some other situations.
  * Added C++11 random number generator support and set it as default.
    There's a new build option CXX11_RNG for srand() compatibility but it'll be
    removed in the future.
  * Moved the player randomize button to the playlist toolbar and replaced the
    icons by a new one.
    - The randomize action shuffles the playlist songs (it doesn't play songs in
      a random way) so it belongs to the playlist. As a result we have a cleaner
      player with fewer buttons.
  * File Browser menu entry moved from Sources to View.
  * Some small context menus refactoring.
  * Updated French, Portuguese and Brazilian Portuguese translations.
  * General code cleanup and small refactorings.

### Removed
  * Player cover zoom doesn't show the CD frame anymore. CD frame is used now
    only in the cover editor.
    The Preferences -> General option "Show CD cover frame in the player" was
    renamed to "Show CD cover frame in the cover editor".

0.5.3 (2024-10-02)
------------------

### Enhancements
  * The playlist isn't cleared anymore if the stop button is clicked twice.
    If we want to clear the playlist, we have the Clear Playlist option
    (menu and playlist toolbar).
  * Splitted README.md installation instructions to INSTALL.md.
  * General code cleanup and small refactorings.

### Bugfixes
  * Fixed the display of several icons that were not shown (Source panel,
    Radio panel->Genres, File Browser->Directories, Library->Treeview/Playlists).

0.5.2 (2024-09-28)
------------------

### Enhancements
  * Updated default compiler standard to C++17.
  * Removed deprecated C++17 register warning.
  * Updated splash screen.
  * Updated copyright headers for the entire project.
  * General code cleanup and small refactorings.

### Removed
  * Removed disabled code for Amazon cover fetcher.

0.5.1 (2024-09-24)
------------------

### Enhancements
  * Updated playlist toolbar icons.
  * Changed library scanning to write partially scanned tracks in the library to
    speed up following rescans.
  * Changed the default lyrics from file/to file to include the album name in the path.

### Bugfixes
  * Fixed compatibility with Gstreamer versions below v1.20.

### Removed
  * Removed unavailable community and home site links, updated splash screen.

0.5.0 (2024-09-22)
------------------

### Enhancements
  * Updated tracks layout in the playlist.
  * Updated Apple deprecated code.
  * ChangeLog converted to Markdown and renamed properly.
  * Updated Portuguese and Brazilian Portuguese translations.
  * Small UI adjustments.

### Bugfixes
  * Fixed playlist drag and drop for wxWidget above 3.2.1.
  * Fixed playlist drag and drop bug introduced by 0.5.0 Beta 4.
  * Fixed playlist to keep the selections when moving multi-selected tracks.
  * Fixed crash opening fullscreen cover window in some systems.
  * Fixed volume after click the player stop button.
  * Fixed taglib 2 compatibility.
  * Fixed the 'Confirm Exit' dialog size.
  * Fixed restoring mouse cursor after access several places in radio and podcasts panels.
  * Reviewed the use of Lock() all over the application.

0.5.0 Beta 4 (2024-09-11)
-------------------------

### Features
  * Added a toolbar in the playlist with actions to manage it (reorder and remove
    tracks, clear the playlist).

### Enhancements
  * Updated some context menu icons in actions related to the playlist.
  * Lyrics configuration changes:
    - Removed hardcoded lyrics path configuration. The lyrics file paths are already
      defined in the lyrics_source configuration.
    - Changed the lyrics "From File" and "To File" path in the default lyrics_source
      configuration. This impact only new installations (the directory now is
      called 'Lyrics' by default).
  * General code cleanup and small refactorings.

### Bugfixes
  * Fixed inconsistency with the right click in the playlist. It doesn't unselect
    the current selection anymore. This turned impossible to apply any action in
    the selection through the context menu.

0.5.0 Beta 3 (2024-09-07)
-------------------------

### Enhancements
  * Added taglib 2 support.
  * Added some missing translations for 'Commands' and 'Copy to' menus.
  * Updated Portuguese and Brazilian Portuguese translations.
  * General code cleanup and small refactorings.

### Bugfixes
  * Fixed bug that crashed Guayadeque when clicking the cover panel to open the
    fullscreen cover window.

0.5.0 Beta 2 (2024-09-05)
-------------------------
###### Thanks to @NullPointerArchitect

### Enhancements
  * Added sqlite3-3.2 support.
  * Added installation instructions for Ubuntu 24.04.
  * Added installation instructions for Arch Linux and optional dependencies.
  * Improved LastFM Panel functionality.
    - Enhanced artist bio section to support both light and dark themes.
    - Adjusted layout to prevent scrollbar overlap by repositioning controls on
      the right side of the panel.
    - Eliminated Events section due to removal of data from the LastFM API.
    - Updated default cover art across all sections.
    - Adjusted layout to allow for longer text in Top Albums, Top Tracks, Similar
      Artists, and Similar Tracks.
    - Fixed a bug causing exponential increase of '&' symbol for artists with '&'
      in their name, potentially leading to system crashes.
  * Updated rating system icons.
    - Changed color of rating stars from black/dark gray to yellow/light gray
      for better visibility.
    - Added black stroke to yellow stars for improved contrast on light themes.
  * Removed all compiler warnings.
  * General code cleanup and small refactorings.

### Bugfixes
  * Fixed bug that crashed Guayadeque when scanning AAC files tags (AAC files
    does not support tags right now).

0.5.0 Beta 1 (2023-11-23)
-------------------------
###### Thanks to @openmonk

### Features
  * Added Best of playlist generator.
  * Added fullscreen cover view on cover panel click.

### Enhancements
  * Added Gstreamer-1.22 and wxwidgets-3.2 support.
  * Added installation instructions for Mageia 9.

### Removed
  * Removed libindicate support.

0.4.7 (2023-02-24)
------------------

  * Added to CoverEditor the option to select a cover from a file and also to
    download it from an url.
  * Enable last.fm cover download.
  * Updated lyric sources.
  * Better gstreamer integration (formats support, audio pipeline reworked).
  * UI changes.
  * Bugfixes.

0.4.6 (2019-06-05)
------------------

  * Bugfixes.

0.4.5 (2017-01-08)
------------------

  * Added proxy support. Configure it from Preferences -> Online.

0.4.3 (2016-11-17)
------------------

  * Added audio cd support.
  * Reduced the tabs height.
  * Moved from Connect to Bind event.
  * Fixed magnatune cover download.
  * Updated Player Control icons.
  * Fixed podcast downloaded filename.
  * Use wxBase64 functions.
  * Dropped internal wxsqlite.
  * Updated to wx3.0.
  * Updated to gstreamer 1.0.
  * Fixed some Config constructor calls.

0.3.7 (2014-02-20)
------------------

  * Removed Flac library dependency. Now flac images are read/writen using taglib.
  * Fixed compilation without external libwxsqlite support.
  * Fixed audio output autoconfiguring option.
  * Fixed load tracks from command line or file manager.
  * Added mpris 2.2 support.
  * Made Guayadeque interface cleaner.
  * Removed bug that crashed Guayadeque when used del in a dynamic playlist.
  * Added TuneIn radio support.
  * Added option to rename podcast channel name.
  * Added option in Preferences -> Playback to write the complete output pipeline.
  * Added Seeked mpris2 signal.
  * Fixed amazon cover download engine.

0.3.5 (2012-02-03)
------------------

  * Allow to select tracks from album browser zoon cover mode.
  * Added load defaults in shortcuts preferences.
  * Added cue support.
  * Allow to change language from Preferences -> General.
  * All playlists but the dynamic playlists with sort defined can be sorted
    by any criteria.
  * Added collections support. You can define as many collections as you want.

0.3.1 (2011-05-13)
------------------

  * Added {al1}, {au1}, {bl1} and {bu1} to lyrics panel patterns for
    lower/upper first letter of artist name and album name.
  * Added compositor and album artist to select context menus.
  * Added a new panel with a tree view of the library.
  * Added option to enable save ratings and playcounts to audio files.
  * Changed command line behaviour to append the tracks to the playlist and
    play it if it was not already playing.
  * Sound menu integration in Ubuntu 11.04 natty.
  * Added shortcuts configurable from preferences.

0.2.9 (2011-02-17)
------------------

  * Added posibility to add more lyrics sources or edit existing ones.
  * Implemented stop after current track using shift + click on stop button.
  * Added more options for Copy To patterns.

 Option | Description
:-------|:-----------
 {al}  | artist in lower case
 {au}  | artist in upper case
 {a1}  | first letter of artist
 {aal} | album artist in lower case
 {aau} | album artist in upper case
 {aa1} | first letter of album artist
 {A}   | album artist if not empty or artist otherwise
 {Al}  | {A} in lower case
 {Au}  | {A} in upper case
 {A1}  | first letter of {A}
 {bl}  | album in lower case
 {bu}  | album in upper case
 {b1}  | first letter of album
 {cl}  | composer in lower case
 {cu}  | composer in upper case
 {c1}  | first letter of composer
 {gl}  | genre in lower case
 {gu}  | genre in upper case
 {g1}  | first letter of genre

  * Added Album Artist to Music Brainz tagger feature.
  * Added combo boxes to the track editor.
  * Added iPod support with covers and playlist.
  * Added output audio device configuration option in preferences.
  * Added partial mpris2 support.
  * Added SoundMenu integration support.
  * Added support for wma files extended attributes.
  * Added the option to disable replay gain in preferences.
  * Added the possibility to show the current track cover in a window.
  * Fixed a bug in default podcast directory creation.
  * Added usb mass storage devices support.
  * Added support for trueaudio files.
  * Added support for wavpack files.
  * Added option to embed album cover to all album tracks.
  * Playlist panel now allow to select multiple playlists.
  * Added an option to dont follow symbolic lyncs while doing the scanning. (Thanks symphom).
  * Added an option to dont search for embedded covers in audio files.
  * Fixed bug not preserving the directory selected for podcasts, recordings or saving lyrics.
  * Added Magnatune support.
  * Added Jamendo support.
  * Added network buffer size option in Preferences -> Online.

0.2.7 (2010-08-26)
------------------

  * Double clicking in audioscroble icon in status bar opens AudioScrobble preferences.
  * Now Preferences opens where it was closed .
  * Added options to delete tracks from library and drive.
  * Implemented reading/writing images into m4a files.
  * Library search covers scan now into audio files too.
  * Added Jump to Next and Previous albums in playlist.
  * Added Album Artist list box to the library tab.
  * Improved library browse speed and memory usage.
  * Added Now Playing searchs to the shoutcast radios.
  * Added in Radio tab the now playing and stream format info.
  * Added in Radio tab the option to reorder columns.
  * Added option in Preferences -> Library tab to add playlists when doing a library scanning.
  * Now playlist are created for found playlist doing a library scan.
  * Added French translation thanks to Frombenny <frombenny@gmail.com>.
  * Added Thailand translation. Thanks to mr_hangman.
  * Added Norwegian translation. Thanks to jente_14.
  * Added icelandic translation. Thanks to Hreinsi.
  * Added text search in album browser.
  * Added support for libre.fm.
  * Added Enqueue as Next option so the selection is added as the next track to be played.
  * Implemented crossfading between tracks.
  * Read composer, comments from ape and m4a files added.
  * Added Lyric support to Ape files.
  * Added option to show full screen and to hide status bar.
  * Implemented live search. Now Enter sends current filtered results to playlist.
  * Added a composer listbox to the library tab.
  * You can enable to delete the recordings not bigger than a certain amount
    of time in preferences.
  * Added a button to record from streams. Need to enable it from Preferences.
  * If no lyric is found after showing the error that was not found restore
    the previous lyric text.
  * Added option to align text in lyrics.
  * Fixed mpris Pause/Play interface.
  * Added lyricsplugin.com as lyrics search engine.
  * Added a playcount listbox to filter in library tab.
  * Added a rating listbox to filter in library tab.
  * Added a year listbox to filter in library tab.
  * Added File Browser. You can navigate throught your files and play them
    directly from Guayadeque.
  * Now the lyrics can be saved to a directory you can configure from Preferences -> Lyrics.
  * Changed the close buttons of the panes.
  * Added search text for player playlist.
  * Now allow to load from command line directories.
  * Now when loading the library if title is empty will be used the filename.
    If album is empty will be used the dir name.
    If Genre or Artist is empty 'Unknown' will be used.
  * Fixed Playlists. Now dynamic playlists are loaded more quickly.
  * Added in Preferences -> Playback the option to add in random mode albums
    instead of tracks.
  * Added two buttons in preferences to order the cover words.
  * The covers are now saved with the first word to detect covers.
  * Added in last.fm panel the possibility to search for tracks in library.
  * The splash shows the revision number.
  * Double click over the track title selects the track.
  * Updated the no cover image. Thanks mrmotinjo.
  * Fix parsing podcasts that contains comments before the channel tag.

0.2.5 (2010-03-12)
------------------

  * Fix set volumen on loading when was muted.
  * Fix Downloading files when redirected using 'location:' in lower case.
  * Fixed when edit the track currently playing the cover dont show anymore.
  * Added german translation.
  * If playlist is empty and player is not playing enqueue tracks starts
    playing the added tracks.
  * Add configuration option to hide close button. You need to add entry in
    the conf file "~/.guayadeque/guayadeque.conf".
    [General]
    ShowPaneCloseButton=0
  * The current played track appears in app title.
  * Fix player labels with & char.
  * Fix drag and drop items in playlist under fedora.
  * Fix # in filenames during drag n drop operations.
  * New Icon and new Splash.

I would like to thank everyone who participated in the Icon development poll
at OMG! UK.  Every icon and every artist was appreciated and the resulting
artwork and design was fantastic.  The 1800 votes cast was a surprise, but
shows how effective a good blog can be. Mrmotinjo (Stefan Bogdanovic
http://evilsun.carbonmade.com ) won with his icon creation and will forever be
linked to Guayadeque and for this we are grateful and humbled.

  * Tracks changes propagates thought the playlist, library, current track, etc.
  * The player slider handles wheel events.
  * Player title, artist or album now scrolls when put the mouse over it if needed.
  * Added composer and comment to the dynamic playlists options.
  * Added dragndrop support to Album Browser. You can drag the tracks or
    with control the cover to another album.
  * Added comments, composer and disk number.
  * Ctrl-A select all itmes in ListBoxes.
  * Select Album cover dialog accepts now a remote url.
  * Added an Album Browser panel where you can view the albums with big covers.
  * Added option to add library path from menu.
  * Added option to rescan the library.
  * Added playback vumeters.
  * You can rearrange panels in PlayLists panel.
  * You can select which filters to show in the library and radio.
  * You can rearrange the panels in the screen.
  * Added support to playlist (m3u,pls,axs,xpfs) to Player. You can drop it
    to player playlist or load it from command line.
  * Corrected a bug editing commands and links in preferences.
  * Added option to repeat the current track.
  * The genre edit field shows now all existing genres to choose one of them .
  * In status bar now is shown the leng of the current selection and the size .
  * If a filter is set the label is highlighted to indicate it even when its hidden.
  * In Lyrics you can paste the content of the clipboard.
  * LyricsPanel accept now drop audio files on it to show the lyrics.
  * Last.fm panel accept now drop audio files on it to show the information.
  * Added italian translation.
  * Added Ultimate-guitar.com as lyrics source for guitar tabs.
  * If the track length is not correctly read by taglib read at play time using gstreamer.
  * Added Events to last.fm information panel.
  * Implemented PlayList import/export from m3u, pls, axs, xspf playlist file formats.
  * Ratings of tracks can be set clicking over the stars in tracks listboxes
    in library and playlists panel.
  * Added an option to export/import user defined radio stations.
    The format is a xml like this:

```xml
	<RadioStations>
	  <RadioStation>
	    <Name>StationName0</Name>
	    <Url>StationLink</Url>
          </RadioStation>
          ...
       </RadioStations>
```
    This way you can do a tool to export radios from other formats and
    import them in Guayadeque.
  * You can select the order of the albums in the albums listbox context menu.
  * You can set the ratings of tracks in playlist directly clicking in the stars.
  * Control Menu show the status of the Smart or Loop mode.
  * Added last.fm as cover source in the cover download dialog.
  * Added a lyric editor in the track editor.
  * Added option to automatically save lyrics to mp3, flac, ogg, m4a files.
    Also you can manually save it from the lyrics panel.
  * Added an option in Preferences -> Playback to remove played tracks.
  * Added print and copy to clipboard of lyrics.
  * Enabled option to edit tracks from the player playlist.
  * When some preferences are modified the settings are propagated where its needed.
  * Fixed bug in smart play mode.

0.2.3 (2010-01-15)
------------------

  * Added Random as a ordering method for dynamic playlists.
  * Added a filter for the random or smart play mode so you can select a
    playlist for the Allow filter and another playlist for the deny filter.
    This way you can for example fix the genre or a label for the Smart
    added tracks from last.fm.
  * Fix bug when searching text with a ' in it.
  * Fix 'Copy to...' when filenames contains reserved chars.
  * Preferences dialog can be resized.
  * You can now select lyrics provider from the lyrics panel.
  * Fixed bug adding a label in the radio label editor.
  * Click over the time can switch between time current track pos or
    time left.
  * Added option in preferences to configure the silence detector. To
    automatically skip track when the sound level gets lower than the one
    you configure.
  * To view the large cover image you just need to put the mouse over the
    player cover image.
  * When you put the mouse over an image in the last.fm panel it will show
    a larger image.
  * Added a Limiter to the sound output.
  * Added a 10 band equalizer.
  * Added a cache for last.fm queries and online images.
  * Fixed crash in mpris when application send incomplete method calls.
  * Fixed bug with library update when library paths changed.
  * Allow to move items in playlists using dragging with mouse.
  * Fixed bug with library paths. After remove a library path the files
    kept in the library.
  * Added drag&drop support to playlists and podcasts panels.
  * Added option to search cover from the track editor image section.
  * Removed mp4v2 library dependency.
  * Removed taglib-extras as taglib now support most of the formats.
  * Allow to load multiple files from file manager.
  * Fixed a bug while dragging files over the playlist.
  * Fixed the support to images in ogg files.
  * Added a navigator in last.fm so you can go to the previous or next track 
    info.
  * Fixed a bug in TrackEditor not saving alls changes made.
  * Changed Save to playlist allowing to append to existing playlist. You
    can select the playlist and where to append (begin, end).
  * Added track counter in the status bar.
  * Added Ukrainian language translation. Thanks yupadmin at gmail dot com.
  * Resizeable track editor. Remembers last position and size.
  * Added gapless play support.
  * Saved in config the showed/hidden panels.
  * Added support to m3u, pls, xspf radio playlists.
  * Added user defined radios.
  * Fixed bug with cmake 2.8.0.
  * Added posibility in progressbar to show counters instead of percent.

0.2.1 (2009-11-27)
------------------

  * Fixed bug with lengths of the podcasts in some cases.
  * The album sort by year only affects now to the Albums list box.
  * Added option to change order of songs in the track editor.
  * Fixed bug restoring saved position and current track index in playlist.
  * Added reload button in lyrics and last.fm panels.
  * Allow filters in the new podcasts dialog.
  * Now can select from a podcast directory "digitalpodcast.com" when adding a new podcast.
  * Limited the length of the description in the podcast channel editor.
  * Fixed bug when the file path had some chars for ex. %.
  * Fixed bug loading tags from songs that didnt exist in library.
  * Fixed loading saved radiostations playlists.
  * Paint podcasts in playlist with length, author and channel.
  * Progressbars in statusbar with labels.
  * Fixed bug creating the podcast default dir.
  * Fixed bug deleting old podcasts.

0.2.0 (2009-11-05)
------------------

  * Fixed LyricWiki lyric search engine.
  * Added support for Podcasts.
  * Only allow to select one radiostation.
  * Added support for musicbrainz search in Track Editor. Its Album
    oriented. Can search for tracks even when no metadata is not found
    using audio fingerprint. Leave empty artist and title fields for this.
  * Added partial support to gnome session. Now save playlist when session is ended.
  * Added support for Discogs cover download. See www.discogs.com.
  * Added cd universe lyric search.
  * Fixed drop files after any element in the player playlist.
  * Added option in Album list box to select a cover file from disk.
  * Fixed the amazon cover download.
  * In Player Playlist selection is cancelled when new playlist is set.
  * Added support to ape file format.
  * Added support to mp4 using libmp4 library. Need libmp4v2 installed.
  * Added column genre to songs list box.
  * Added support to flac, ogg and mpc file formats.
  * TaskBar Icon is created/removed if enabled/disabled from preferences.
  * Fixed bug in playlist not allowing to delete more than one track if the
    first track is selected.
  * Albums list box will show the albums with the latest year only.
  * Added LeoLyrics lyric search http://leoslyrics.com/.
  * Fixed bug in radio stations list box ordering.

0.1.5 (2009-08-04)
------------------

  * Lyrics panel allow to enter any track name for manual lyrics search.
  * Clicking in Songs List box selects the sorting of the tracks.
  * Added an option to save/restore playing position when track is bigger than the
    length specified in preferences.
  * Fixed bug in library updated when only changed dir name.
  * Added option in last.fm panel to copy element info text to clipboard.
  * Update the library automatically if detects an old version installed.
  * Tracks passed in command line will be played by default.
  * Edited tracks will be updated if it was in player playlist.
  * Implemented Playlists. Static and Dynamic.
  * Fixed crash when trying to read tags from a missing file.
  * The track playcount is updated when the track have been played at least
    the half of its length.
  * Fixed a bug in player. Now Prev Track when stopped update the info.
  * Now you can edit the rating of a track from the Player current track
    info. To do it move the mouse up and down while clicking on rating starts.
  * Added bitrate, rating, playcount, lastplay, added time  to tracks database.
  * Fixed crash when using 'Edit labes' in artists or songs with no artist
    or no songs selected.

0.1.1 (2009-06-25)
------------------

  * Play/Enqueue in RadioStations was not implemented. Fixed now.
  * Added Custom commands that are accesible from contextual menu in Artist,
    Albums, Songs and Playlist .
  * Removed the need of the wxWidgets media library not present by default
    in many distributions.
  * Added amazon search engine for covers.
  * The new/updated/removed covers are updated in library too.
  * Double click on artistname or albumname in player panel current track
    will select the artist or the album in the library.
  * Fixed bug in cover editor that blocked gui randomly.
  * The tracks editor now can edit images stored in id3tags.
  * Fixed bug saving special chars to id3 tags.
  * Player shows the cover stored in the id3tags before attempt to load the
    album cover.
  * Added support to ReplayGain tags.
  * Show the bitrate of the current track.
  * Improved library update. Now more faster.
  * Added Play/Enqueue options to Last.fm panel items.
  * Playlist current track now follow theme color.
  * Last.fm preferences shouldn't be enabled if the user or pass is not
    filled.
  * Mouse wheel support in the volume control window.
  * Create ~/.guayadeque/LinkIcons dir if doesnt exists to store the
    Links Icons.

0.1.0 (2009-06-09)
------------------

  * Now if Next Track is clicked at the last track in playlist and Play Random
    is enabled it will add a new random track to the playlist.
  * Fixed bug in some listbox that made the context menu to appear twice.
  * Fixed a bug when dragging tracks in the playlist and the list were
    scrolled down.
  * The Links now have names. So you can have multiple links with same host
    Edit the names in Preferences -> Links.
  * Added Edit Labels Option to Playlist tracks.
  * Added the year to the player information.
  * Added the links also to the library panel context menu.
  * The year is shown in the albums list box.
  * Added two options to play or enqueue all tracks in the songs list box.
  * Now from the label editor can be added or deleted the labels too.
  * Fixed a bug when Start Minimized was enabled and not the TaskBar icon.
  * Implemented the option to add a random track if the playlist is empty.
  * Fixed bug in manual cover downloader when the results where below 10.
  * The order of radiostations preference is saved.
  * Added an option to allow albums be ordered by Year.
  * Now the database has version for future updates.
  * If covers are updated it will be changed in database. If you had older version
    you need to delete the old database ~/.guayadeque/guayadeque.db.
  * Now can be updated only the selected RadioGenres and not all as before.
  * Added support for Multimedia Keys (Play,Pause,Stop,Next,Prev)
  * Fixed a bug when searching text in radio panel introduced in v0.0.3.
  * Fixed a bug when pulsed random with only one track in playlist.
  * Fixed the load of the year field of the saved playlist tracks.
  * Added support for mpris dbus protocol. See http://wiki.xmms2.xmms.se/wiki/MPRIS.
  * Fixed support for translations.
  * Fixed bug saving the labels to the mp3 files.
  * Fixed bug that prevented to get info (lastfm, lyrics) for some names
    with special chars.
  * Now the hidden categories in LastFM Panel gets saved on close.
  * Fixed bug that prevented to load files with some special chars.
  * Fixed colors in LastFM and Lyrics panel to follow theme.
  * ListBox colors now follow current theme.
  * Removed bug in Track editor year field.
  * Changed from libid3 to taglib as need id3 v2.4 support. Be aware that
    not all program will read ID3 v2.4 tags. For example if you use easytag
    you should use the v2.1.1 or later.

0.0.3 Beta (2009-05-12)
-----------------------

  * Added Labels in Radio panel. This change needed a database schema change
    so if you had an older version you need to remove ~/.guayadeque/guayadeque.db.
  * Fixed some minor bugs.

0.0.2 Beta (2009-04-06)
-----------------------

  * Fixed manual cover downloader.
  * Added progress bar to cover editor.
  * Added support to translations.
  * Fixed bug in ListBox colors.

0.0.1 Beta (2009-03-11)
-----------------------

  * First Public release.
