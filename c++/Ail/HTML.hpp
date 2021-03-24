////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __HTML_H__
#define __HTML_H__

#pragma once

_BEGIN_NAMESPACE_
////////////////////////////////////////////////////////////////////////////////////////
// HTML keywords
// ---- --------
// Comments. Any text between tags will not display in the browser.
const tchar ConstHTML_Comment[]    = _t("!");
// Describes the HTML version used in the current document.
const tchar ConstHTML_DOCTYPE[]    = _t("!DOCTYPE");
// Stands for anchor. HREF= attribute creates hyperlinks. NAME= attribute creates a named reference.
const tchar ConstHTML_A[]          = _t("A");
// Specifies a mailing address.
const tchar ConstHTML_ADDRESS[]    = _t("ADDRESS");
// Embeds a Java applet. See OBJECT.
const tchar ConstHTML_APPLET[]     = _t("APPLET");
// Specifies the shape of a "hot spot" in a client-side image map.
const tchar ConstHTML_AREA[]       = _t("AREA");
// Changes text to bold. See STRONG.
const tchar ConstHTML_B[]          = _t("B");
// Specifies a document's URL.
const tchar ConstHTML_BASE[]       = _t("BASE");
// Sets the base font value.
const tchar ConstHTML_BASEFONT[]   = _t("BASEFONT");
// Adds background sounds that play on initial load.
const tchar ConstHTML_BGSOUND[]    = _t("BGSOUND");
// Enlarges the font size.
const tchar ConstHTML_BIG[]        = _t("BIG");
// Sets apart a quotation in text.
const tchar ConstHTML_BLOCKQUOTE[] = _t("BLOCKQUOTE");
// Specifies the beginning and the end of the document body. See HEAD.
const tchar ConstHTML_BODY[]       = _t("BODY");
// Inserts a line break.
const tchar ConstHTML_BR[]         = _t("BR");
// Specifies a caption for a table. Valid only within the TABLE element.
const tchar ConstHTML_CAPTION[]    = _t("CAPTION");
// Centers text and images.
const tchar ConstHTML_CENTER[]     = _t("CENTER");
// Indicates a citation. Used to present a book, paper, or other published source material.
const tchar ConstHTML_CITE[]       = _t("CITE");
// Presents a code sample.
const tchar ConstHTML_CODE[]       = _t("CODE");
// Sets the properties of a column.
const tchar ConstHTML_COL[]        = _t("COL");
// Sets the properties of one or more columns as a group.
const tchar ConstHTML_COLGROUP[]   = _t("COLGROUP");
// Indicates a comment. Text in a comment element does not display in a browser.
const tchar ConstHTML_COMMENT[]    = _t("COMMENT");
// Specifies definition data. Used to format the text for a definition. See DL, DT.
const tchar ConstHTML_DD[]         = _t("DD");
// Specifies a definition. Formats a defined term.
const tchar ConstHTML_DFN[]        = _t("DFN");
// Denotes a directory list.
const tchar ConstHTML_DIR[]        = _t("DIR");
// Sets a document division. Groups related elements together within a document.
const tchar ConstHTML_DIV[]        = _t("DIV");
// Denotes a definition list. Used for a list of defined terms. See DT, DD.
const tchar ConstHTML_DL[]         = _t("DL");
// Specifies a definition term. Used to format the defined term. See DL, DD.
const tchar ConstHTML_DT[]         = _t("DT");
// Emphasizes text, usually by rendering text in italics.
const tchar ConstHTML_EM[]         = _t("EM");
// Indicates an embedded object. See OBJECT.
const tchar ConstHTML_EMBED[]      = _t("EMBED");
// Formats the font style, size, and color.
const tchar ConstHTML_FONT[]       = _t("FONT");
// Denotes a form with which users enter data. See INPUT for a list of form elements.
const tchar ConstHTML_FORM[]       = _t("FORM");
// Defines independent windows, or frames, within a page. See FRAMESET.
const tchar ConstHTML_FRAME[]      = _t("FRAME");
// Defines layout for frames within a page. See FRAME.
const tchar ConstHTML_FRAMESET[]   = _t("FRAMESET");
// Renders text in heading style, usually with a larger font than the body text. The n is a value from 1 to 6.
const tchar ConstHTML_Hn[]         = _t("Hn");
// Marks the HTML document heading.
const tchar ConstHTML_HEAD[]       = _t("HEAD");
// Draws a horizontal rule. Used to separate sections.
const tchar ConstHTML_HR[]         = _t("HR");
// Denotes the file is an HTML document.
const tchar ConstHTML_HTML[]       = _t("HTML");
// Renders text in italics.
const tchar ConstHTML_I[]          = _t("I");
// Inserts a graphic file.
const tchar ConstHTML_IMG[]        = _t("IMG");
// Specifies a form control such as a check box or radio button. See FORM.
const tchar ConstHTML_INPUT[]      = _t("INPUT");
// Indicates the presence of an index.
const tchar ConstHTML_ISINDEX[]    = _t("ISINDEX");
// Indicates text to be entered at a keyboard. Appears in fixed-width and bold type.
const tchar ConstHTML_KBD[]        = _t("KBD");
// Denotes an item in a list. Adds special character or number depending on use. See UL
const tchar ConstHTML_LI[]         = _t("LI");
// Establishes the relationship between documents. Appears only in the HEAD element.
const tchar ConstHTML_LINK[]       = _t("LINK");
// Renders text in fixed-width type.
const tchar ConstHTML_LISTING[]    = _t("LISTING");
// Specifies a collection of hot spots for a client-side image map.
const tchar ConstHTML_MAP[]        = _t("MAP");
// Displays text in a scrolling marquee.
const tchar ConstHTML_MARQUEE[]    = _t("MARQUEE");
// Denotes a list of items.
const tchar ConstHTML_MENU[]       = _t("MENU");
// Provides information about the document. Used for client pull, also by some search engines for indexing.
const tchar ConstHTML_META[]       = _t("META");
// Turns off line breaking.
const tchar ConstHTML_NOBR[]       = _t("NOBR");
// Indicates content viewable only by browsers that do not support frames.
const tchar ConstHTML_NOFRAMES[]   = _t("NOFRAMES");
// Inserts an OLE Control.
const tchar ConstHTML_OBJECT[]     = _t("OBJECT");
// Specifies an ordered list. Each item has a number or letter reference. See UL, LI.
const tchar ConstHTML_OL[]         = _t("OL");
// Denotes one choice in a list box.
const tchar ConstHTML_OPTION[]     = _t("OPTION");
// Inserts a paragraph break and denotes a new paragraph.
const tchar ConstHTML_P[]          = _t("P");
// Sets object properties.
const tchar ConstHTML_PARAM[]      = _t("PARAM");
// Renders text in fixed-width type without processing elements.
const tchar ConstHTML_PLAINTEXT[]  = _t("PLAINTEXT");
// Displays text exactly as typed-with all line breaks and spacing.
const tchar ConstHTML_PRE[]        = _t("PRE");
// Renders text in strikethrough type.
const tchar ConstHTML_S[]          = _t("S");
// Specifies sample text. See CODE.
const tchar ConstHTML_SAMP[]       = _t("SAMP");
// Specifies the inclusion of a script.
const tchar ConstHTML_SCRIPT[]     = _t("SCRIPT");
// Denotes a list box or dropdown list.
const tchar ConstHTML_SELECT[]     = _t("SELECT");
// Decreases the font size.
const tchar ConstHTML_SMALL[]      = _t("SMALL");
// Applies style information to the enclosed text.
const tchar ConstHTML_SPAN[]       = _t("SPAN");
// Renders text in strikethrough type. See S.
const tchar ConstHTML_STRIKE[]     = _t("STRIKE");
// Emphasizes text, usually with bold. See B.
const tchar ConstHTML_STRONG[]     = _t("STRONG");
// Renders text in subscript
const tchar ConstHTML_SUB[]        = _t("SUB");
// Renders text in superscript.
const tchar ConstHTML_SUP[]        = _t("SUP");
// Creates a table. See TH, TR, and TD to learn how to define rows and columns.
const tchar ConstHTML_TABLE[]      = _t("TABLE");
// Defines the table body.
const tchar ConstHTML_TBODY[]      = _t("TBODY");
// Creates a cell in a table.
const tchar ConstHTML_TD[]         = _t("TD");
// Creates a cell in a table.
const tchar ConstHTML_TFOOT[]      = _t("TFOOT");
// Creates a row or column heading in a table.
const tchar ConstHTML_TH[]         = _t("TH");
// Defines the table header.
const tchar ConstHTML_THEAD[]      = _t("THEAD");
// Creates a box in which a user can enter and edit text.
const tchar ConstHTML_TEXTAREA[]   = _t("TEXTAREA");
// Specifies a document title. Appears in the browser title bar.
const tchar ConstHTML_TITLE[]      = _t("TITLE");
// Creates a row in a table.
const tchar ConstHTML_TR[]         = _t("TR");
// Denotes teletype. Displays text in fixed-width type.
const tchar ConstHTML_TT[]         = _t("TT");
// Renders text underlined.
const tchar ConstHTML_U[]          = _t("U");
// Formats lines of text as a bulleted list. See LI.
const tchar ConstHTML_UL[]         = _t("UL");
// Indicates placeholder text for a variable. Displays text in a small, fixed-width font.
const tchar ConstHTML_VAR[]        = _t("VAR");
// Inserts a soft line break in a block of NOBR text.
const tchar ConstHTML_WBR[]        = _t("WBR");
// Indicates example text. Displays text in fixed-width font.
const tchar ConstHTML_XMP[]        = _t("XMP");
////////////////////////////////////////////////////////////////////////////////////////
_END_NAMESPACE_

#endif // __HTML_H__
