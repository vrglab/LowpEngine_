using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace GlobalUtilities.IO
{
    public class IniFile
    {
        string Path;
        string EXE = Assembly.GetExecutingAssembly().GetName().Name;

        [DllImport("kernel32", CharSet = CharSet.Unicode)]
        static extern long WritePrivateProfileString(string Section, string Key, string Value, string FilePath);

        [DllImport("kernel32", CharSet = CharSet.Unicode)]
        static extern int GetPrivateProfileString(string Section, string Key, string Default, StringBuilder RetVal,
            int Size, string FilePath);

        public IniFile(string IniPath = null)
        {
            Path = new FileInfo(IniPath ?? EXE + ".ini").FullName;
        }

        public string Read(string Key, string Section = null)
        {
            var RetVal = new StringBuilder(255);
            GetPrivateProfileString(Section ?? EXE, Key, "", RetVal, 255, Path);
            return RetVal.ToString();
        }

        public void Write(string Key, string Value, string Section = null)
        {
            WritePrivateProfileString(Section ?? EXE, Key, Value, Path);
        }

        public void DeleteKey(string Key, string Section = null)
        {
            Write(Key, null, Section ?? EXE);
        }

        public void DeleteSection(string Section = null)
        {
            Write(null, null, Section ?? EXE);
        }

        public bool KeyExists(string Key, string Section = null)
        {
            return Read(Key, Section).Length > 0;
        }

        public Dictionary<string, string> ReadSection(string Section = null)
        {
            var sectionData = new Dictionary<string, string>();
            var keysBuffer = new StringBuilder(2048); // Adjust the buffer size as needed

            int bytesRead = GetPrivateProfileString(Section ?? EXE, null, "", keysBuffer, keysBuffer.Capacity, Path);

            if (bytesRead > 0)
            {
                var keys = keysBuffer.ToString().Split('\0');

                foreach (var key in keys)
                {
                    if (!string.IsNullOrEmpty(key))
                    {
                        string value = Read(key, Section);
                        sectionData[key] = value;
                    }
                }
            }

            return sectionData;
        }
    }
}
