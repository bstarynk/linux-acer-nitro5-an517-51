// file cmd_basile.cpp is dual-licensed GPLv3+ or MIT

/***
// © Copyright 2020 by Basile Starynkevitch
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *    This file "cmd_basile.cpp" is free software, you can use it,
 *    modify it, and redistribute it either, and at your choice, under
 *    GPLv3+ license above, or under MIT license below:
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 ***/

#include <map>
#include <vector>
#include <fstream>

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <curl.h>

extern "C" {
#include "sash.h"
};

int     do_curl(int argc, const char**argv) {

    std::clog << "unimplemented do_curl:";
    for (int i=0; i<argc; i++)
        std::clog << ' ' << argv[i];
    std::clog << std::endl;
    return 2;
} // end do_curl


char*
basile_prompt(void)
{
    static std::string prstr;
    std::string curprompt{prompt};
    if (curprompt.empty()) {
        curprompt = std::string((getuid()==0)?"sash#":"sash>");
    }
    else {
        const char* pc = prompt;
        const char* next = nullptr;
        for (ix=0; ix>=0; ix++) {
            pc = curprompt.c_str()+ix;
            if (*pc == '\0')
                break;
            const char*percent = strchr(pc, '%');
            if (percent) {
                ix++;
                if (percent[1] == '%')
                {
                    prstr += '%';
                }
                else if (percent[1] == '~')
                {
                    const char*cwd = get_current_dir_name();
                    if (cwd) prstr += cwd;
                    else prstr += '?';
                    free (cwd);
                }
                else if (percent[1] == 'T')
                {
                    time_t nowt = time(nullptr);
                    struct tm nowtm;
                    char timbuf[80];
                    memset(&tm, 0, sizeof(tm));
                    memset(timbuf, 0, sizeof(timbuf));
                    localtime_r(&nowt, &nowtm);
                    strftime(timbuf, sizeof(timbuf), "%H:%M:%S %Z", nowtm);
                    prstr += timbuf;
                }
                else if (percent[1] == 'D')
                {
                    time_t nowt = time(nullptr);
                    struct tm nowtm;
                    char timbuf[80];
                    memset(&tm, 0, sizeof(tm));
                    memset(timbuf, 0, sizeof(timbuf));
                    localtime_r(&nowt, &nowtm);
                    strftime(timbuf, sizeof(timbuf), "%Y/%b/%d", nowtm);
                    prstr += timbuf;
                }
                else if (percent[1] == 't')
                {
                    char timbuf[32];
                    memset (timbuf, 0, sizeof(timbuf));
                    snprintf(timbuf, sizeof(timbuf), "%.2f", sash_time(CLOCK_PROCESS_CPUTIME_ID));
                    prstr += timbuf;
                }
                else if (percent[1] == '$')
                {
                    char pidbuf[32];
                    memset(pidbuf, 0, sizeof(pidbuf));
                    snprintf(pidbuf, sizeof(pidbuf), "%ld", (long)getpid());
                    prstr += pidbuf;
                }
                else if (percent[1] == '#') {
                    if (getuid())
                        prstr += "%";
                    else
                        prstr += "#";
                }
                else {
                    prstr += percent[1];
                }
            }
            else {// no percent
                prstr += *pc;
            }
        }
    }
    if (!prstr.empty())
        return prstr.c_str();
    else return nullptr;
} // end basile_prompt
