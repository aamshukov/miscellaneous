#region copyright
//......................................................................................
// This is a part of UI Soft Library.  1989-2006 UI Soft Inc.               .
//......................................................................................
// THIS CODE MAY BE USED, COPIED, STORED, OR DISTRIBUTED ONLY IN ACCORDANCE WITH       .
// A WRITTEN LICENSE AGREEMENT AND WITH THE INCLUSION OF THIS COPYRIGHT NOTICE.        .
//......................................................................................
#endregion

#region prolog
// file       : 
// description: Error
// package    : ail.net.parser
//
#endregion

#region import
using System;
#endregion

namespace ail.net.parser
{
    /// <summary>
    /// summary description for Error
    /// </summary>
    public class Error
    {
        #region constants
        public enum ELevel
        {
            eWarning,
            eSevere,
            eCritical
        };

        public const int kMaxErrorCost = 5;
        #endregion // constants

        #region data members
        int     IdAttr;                         // error number
        ail.net.parser.Error.ELevel LevelAttr;  // level
        int     OffsetAttr;                     // offset in context (absolute address)
        int     PositionAttr;                   // position in line (relative address)
        int     LineAttr;                       // line number (relative address)
        string  TextAttr;                       // message
        string  ContributorAttr;                // who introduced this error
        #endregion // data members

        #region ctor/dtor/finalizer
        public Error()
        {
        }

        public Error(int xi_id, int xi_offset, int xi_position, int xi_line, string xi_text, string xi_contributor)
        {
            IdAttr          = xi_id;
            OffsetAttr      = xi_offset;
            PositionAttr    = xi_position;
            LineAttr        = xi_line;
            TextAttr        = xi_text;
            ContributorAttr = xi_contributor;
        }
        #endregion ctor/dtor/finalizer

        #region properties
        int Id
        {
            get
            {
                return IdAttr;
            }

            set
            {
                IdAttr = value;
            }
        }

        public ail.net.parser.Error.ELevel Level
        {
            get
            {
                return LevelAttr;
            }

            set
            {
                LevelAttr = value;
            }
        }

        int Offset
        {
            get
            {
                return OffsetAttr;
            }

            set
            {
                OffsetAttr = value;
            }
        }

        int Position
        {
            get
            {
                return PositionAttr;
            }

            set
            {
                PositionAttr = value;
            }
        }

        int Line
        {
            get
            {
                return LineAttr;
            }

            set
            {
                LineAttr = value;
            }
        }

        string Text
        {
            get
            {
                return TextAttr;
            }

            set
            {
                TextAttr = value;
            }
        }

        string Contributor
        {
            get
            {
                return ContributorAttr;
            }

            set
            {
                ContributorAttr = value;
            }
        }
        #endregion // properties

        #region methods
        public static ail.net.parser.Error CreateError(int xi_id, int xi_offset, int xi_position, int xi_line, string xi_text, string xi_contributor)
        {
            ail.net.parser.Error result = new Error(xi_id, xi_offset, xi_position, xi_line, xi_text, xi_contributor);
            return result;
        }
        #endregion // methods
    }
}

#region epilog
#endregion
