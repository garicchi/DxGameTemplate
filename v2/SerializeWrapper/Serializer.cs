using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using Windows.Storage.Streams;
using System.IO;

namespace SerializeWrapper
{
    public sealed class Serializer
    {
        //private DataContractSerializer _serializer;
        public Serializer(Type type)
        {
            //_serializer = new DataContractSerializer(type);
        }

        public void Write(IOutputStream oStream,Object obj)
        {
           /* Stream stream = oStream.AsStreamForWrite();
            _serializer.WriteObject(stream,obj);
            * */
        }

        public Object Read(IInputStream iStream)
        {
            /*
            Stream stream = iStream.AsStreamForRead();
            return _serializer.ReadObject(stream);
             * */
            return null;
        }
    }
}
