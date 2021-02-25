#region copyright
//......................................................................................
// This is a part of UI Soft Library. Copyright © 1989-2006 UI Soft Inc.               .
//......................................................................................
// THIS CODE MAY BE USED, COPIED, STORED, OR DISTRIBUTED ONLY IN ACCORDANCE WITH       .
// A WRITTEN LICENSE AGREEMENT AND WITH THE INCLUSION OF THIS COPYRIGHT NOTICE.        .
//......................................................................................
#endregion

#region prolog
// file       : 
// description: Context
// package    : ail.net.parser
//
#endregion

#region import
using System;
using System.IO;
using System.Text;
#endregion

namespace ail.net.parser
{
    /// <summary>
    /// summary description for Context
    /// </summary>
    public class Context : IDisposable
    {
        #region constants
        public static char kEndOfStream = (char)0xFFFF;

        public enum ELoadMedia
        {
            eMediaString,
            eMediaFile
        };
        #endregion // constants

        #region data members
        private int     CountAttr;      // how many symbols
        private int     CapacityAttr;   // capacity of buffer
        private char [] DataAttr;       // array of unicode characters, buffer
        #endregion // data members

        #region ctor/dtor/finalizer
        public Context()
        {
        }

        ~Context()
        {
            Dispose(false);
        }
        #endregion ctor/dtor/finalizer

        #region properties
        public int Count
        {
            get
            {
                return CountAttr;
            }

            set
            {
                CountAttr = value;
            }
        }

        public int Capacity
        {
            get
            {
                return CapacityAttr;
            }

            set
            {
                CapacityAttr = value;
            }
        }

        public char [] Data
        {
            get
            {
                return DataAttr;
            }

            set
            {
                DataAttr = value;
            }
        }
        #endregion // properties

        #region methods
        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this); 
        }

        protected virtual void Dispose(bool xi_disposing)
        {
            if(xi_disposing)
            {
                // free managed objects
                Deallocate();
            }

            // free unmanaged objects, including base class
            // set large fields to null (de-reference)
        }

        public bool IsLE(byte [] buffer)
        {
            ail.net.framework.Assert.NonNullReference(buffer, "buffer");
            ail.net.framework.Assert.NotOutOfRange(buffer.Length, 0, 2, "buffer");
			return buffer[0] == 0xFF && buffer[1] == 0xFE;
		}

        public bool IsBE(byte [] buffer)
        {
            ail.net.framework.Assert.NonNullReference(buffer, "buffer");
            ail.net.framework.Assert.NotOutOfRange(buffer.Length, 0, 2, "buffer");
			return buffer[0] == 0xFE && buffer[1] == 0xFF;
        }

        public bool IsUnmarked(byte [] buffer)
        {
            ail.net.framework.Assert.NonNullReference(buffer, "buffer");
            ail.net.framework.Assert.NotOutOfRange(buffer.Length, 0, 2, "buffer");
            return !(IsLE(buffer) || IsBE(buffer));
        }

        public void Allocate(int xi_count)
        {
            Deallocate();

            Count	 = xi_count;
            Capacity = ail.net.framework.Functor.Align(xi_count+1+2, ail.net.framework.Functor.kAlignValue); // +1 for '0' and +2 for BOM, byte order modifier
            Data     = new char[Capacity];
        }

        public void Deallocate()
        {
            Count    = 0;
            Capacity = 0;
            Data     = null;
        }

		public void Load(string xi_str, ail.net.parser.Context.ELoadMedia xi_media)
		{
			ail.net.framework.Assert.NonEmptyString(xi_str, "xi_str");

			if(xi_media == ail.net.parser.Context.ELoadMedia.eMediaString)
			{
			    Allocate(xi_str.Length);

			    StringReader reader = new StringReader(xi_str);

			    int read = reader.Read(Data, 0, xi_str.Length);

                Count = Math.Max(0, Math.Min(read, xi_str.Length));

			    Data[Count] = ail.net.parser.Context.kEndOfStream;
            }
            else if(xi_media == ail.net.parser.Context.ELoadMedia.eMediaFile)
            {
                StreamReader reader = new StreamReader(xi_str);
                Load(reader.BaseStream);
            }
		}

        public void Load(Stream xi_stream)
        {
            ail.net.framework.Assert.NonNullReference(xi_stream, "xi_stream");

            Encoding encoder = null;

            xi_stream.Seek(0, SeekOrigin.Begin);

            byte [] buffer = new byte[2];

            int count = xi_stream.Read(buffer, 0, 2);

            if(count == 2 && (IsLE(buffer) || IsBE(buffer)))
            {
                count   = (int)((xi_stream.Length-2)/2); // UNICODE
                encoder = new UnicodeEncoding();
            }
            else
            {
                count   = (int)xi_stream.Length; // UTF8 or ASCII
				encoder = new UTF8Encoding();
			}

            Allocate(count);

            xi_stream.Seek(0, SeekOrigin.Begin);

            StreamReader reader = new StreamReader(xi_stream, encoder);

            int read = reader.Read(Data, 0, count);
            
            Count = Math.Max(0, Math.Min(read, count));

            Data[Count] = ail.net.parser.Context.kEndOfStream;
        }
        #endregion // methods
    }
}

#region epilog
#endregion
