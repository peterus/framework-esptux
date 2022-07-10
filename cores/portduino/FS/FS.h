/*
 FS.h - file system wrapper
 Copyright (c) 2015 Ivan Grokhotkov. All rights reserved.
 This file is part of the esp8266 core for Arduino environment.

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef FS_H_
#define FS_H_

//#include <Arduino.h>
#include <Stream.h>
#include <memory>

#include "FSImpl.h"

namespace fs {

#define FILE_READ   "r"
#define FILE_WRITE  "w"
#define FILE_APPEND "a"

class File : public Stream {
public:
  File(FileImplPtr p = FileImplPtr());

  size_t write(uint8_t) override;
  size_t write(const uint8_t *buf, size_t size) override;
  int    available() override;
  int    read() override;
  int    peek() override;
  void   flush() override;
  size_t read(uint8_t *buf, size_t size);
  size_t readBytes(char *buffer, size_t length);

  bool seek(uint32_t pos, SeekMode mode);
  bool seek(uint32_t pos);

  size_t position() const;
  size_t size() const;
  void   close();

  operator bool() const;

  time_t      getLastWrite();
  const char *name() const;

  bool isDirectory(void);
  File openNextFile(const char *mode = FILE_READ);
  void rewindDirectory(void);

protected:
  FileImplPtr _p;
};

class FS {
public:
  FS(FSImplPtr impl) : _impl(impl) {
  }

  File open(const char *path, const char *mode = FILE_READ);
  File open(const String &path, const char *mode = FILE_READ);

  bool exists(const char *path);
  bool exists(const String &path);

  bool remove(const char *path);
  bool remove(const String &path);

  bool rename(const char *pathFrom, const char *pathTo);
  bool rename(const String &pathFrom, const String &pathTo);

  bool mkdir(const char *path);
  bool mkdir(const String &path);

  bool rmdir(const char *path);
  bool rmdir(const String &path);

protected:
  FSImplPtr _impl;
};

} // namespace fs

#ifndef FS_NO_GLOBALS
using fs::File;
using fs::FS;
using fs::SeekCur;
using fs::SeekEnd;
using fs::SeekMode;
using fs::SeekSet;
#endif // FS_NO_GLOBALS

#endif
