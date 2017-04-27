// ----------------------------------------------------------------------------
// JsonStream.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef _JSON_STREAM_DEFINITIONS_H_
#define _JSON_STREAM_DEFINITIONS_H_


template<typename K, typename T>
void JsonStream::write(K key, T value)
{
  writeKey(key);
  write(value);
}

template<typename K, typename T>
void JsonStream::writeDouble(K key, T value, unsigned char prec)
{
  writeKey(key);
  writeDouble(value,prec);
}

template<typename K>
void JsonStream::writeNull(K key)
{
  writeKey(key);
  writeNull();
}

template<typename K, typename T>
void JsonStream::writeJson(K key, T value)
{
  writeKey(key);
  writeJson(value);
}

template <typename T, size_t N>
void JsonStream::write(T (& values)[N])
{
  if (stream_ptr_ != NULL)
  {
    endArrayItem();
    beginArray();
    for (int i=0;i<N;++i)
    {
      write(values[i]);
    }
    endArray();
  }
}

template <size_t N>
void JsonStream::write(const char (& values)[N])
{
  write<const char *>(values);
}

template <size_t N>
void JsonStream::write(char (& values)[N])
{
  write<char *>(values);
}

template <typename K, typename T, size_t N>
void JsonStream::write(K key, T (& values)[N])
{
  writeKey(key);
  write(values);
}

template <typename T>
void JsonStream::writeArray(T * values, const size_t N)
{
  if (stream_ptr_ != NULL)
  {
    endArrayItem();
    beginArray();
    for (int i=0;i<N;++i)
    {
      write(values[i]);
    }
    endArray();
  }
}

template <typename K, typename T>
void JsonStream::writeArray(K key, T * values, const size_t N)
{
  writeKey(key);
  writeArray(values,N);
}

template <typename T, size_t N>
void JsonStream::write(Array<T,N> & values)
{
  if (stream_ptr_ != NULL)
  {
    endArrayItem();
    beginArray();
    for (int i=0;i<values.size();++i)
    {
      write(values[i]);
    }
    endArray();
  }
}

template <typename T>
void JsonStream::write(Vector<T> & values)
{
  if (stream_ptr_ != NULL)
  {
    endArrayItem();
    beginArray();
    for (int i=0;i<values.size();++i)
    {
      write(values[i]);
    }
    endArray();
  }
}

template <size_t N>
long JsonStream::readJsonIntoBuffer(char (&buffer)[N])
{
  if (stream_ptr_ != NULL)
  {
    size_t bytes_read = stream_ptr_->readBytesUntil(EOL,buffer,N);
    if (bytes_read < N)
    {
      // terminate string
      buffer[bytes_read] = 0;
    }
    else
    {
      // set buffer to empty string
      buffer[0] = 0;
      // clear stream of remaining characters
      char EOL_STR[2];
      EOL_STR[0] = EOL;
      EOL_STR[1] = 0;
      stream_ptr_->find(EOL_STR);
      return -1;
    }
    return bytes_read;
  }
  else
  {
    return 0;
  }
}

#endif
