//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// UNSUPPORTED: c++98, c++03, c++11, c++14
// XFAIL: windows

// <fstream>

// basic_filebuf<charT,traits>* open(const filesystem::path& p, ios_base::openmode mode);

#include <fstream>
#include <filesystem>
#include <cassert>
#include "test_macros.h"
#include "platform_support.h"

namespace fs = std::filesystem;

int main(int, char**) {

  fs::path p = get_temp_file_name();
  {
    std::filebuf f;
    assert(f.open(p, std::ios_base::out) != 0);
    assert(f.is_open());
    assert(f.sputn("123", 3) == 3);
  }
  {
    std::filebuf f;
    assert(f.open(p, std::ios_base::in) != 0);
    assert(f.is_open());
    assert(f.sbumpc() == '1');
    assert(f.sbumpc() == '2');
    assert(f.sbumpc() == '3');
  }
  std::remove(p.c_str());
  {
    std::wfilebuf f;
    assert(f.open(p, std::ios_base::out) != 0);
    assert(f.is_open());
    assert(f.sputn(L"123", 3) == 3);
  }
  {
    std::wfilebuf f;
    assert(f.open(p, std::ios_base::in) != 0);
    assert(f.is_open());
    assert(f.sbumpc() == L'1');
    assert(f.sbumpc() == L'2');
    assert(f.sbumpc() == L'3');
  }
  remove(p.c_str());

  return 0;
}
