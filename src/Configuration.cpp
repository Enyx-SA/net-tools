/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 EnyxSA
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "Configuration.hpp"

#include <stdexcept>
#include <iostream>

#include <boost/regex.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace enyx {
namespace tcp_tester {

namespace {

uint64_t
parse_size(const std::string & s)
{
    boost::regex r("(\\d+)\\s*([KMG]?)([bB])");
    boost::smatch m;

    if (! boost::regex_match(s, m, r))
    {
        std::ostringstream error;
        error << "size '" << s
              << "' doesn't match \\d+\\s*[KMG]?[bB]";
        throw std::runtime_error(error.str());
    }

    uint64_t size = std::atoll(m.str(1).c_str());

    if (m[2].matched)
        switch (m.str(2)[0])
        {
        case 'G':
            size *= 1024;
        case 'M':
            size *= 1024;
        case 'K':
            size *= 1024;
        }

    if (m.str(3) == "b")
        size /= 8;

    return size;
}

} // anonymous namespace

std::istream &
operator>>(std::istream & in, Configuration::Verify & verify)
{
    std::istream::sentry sentry(in);

    if (sentry)
    {
        std::string s;
        in >> s;

        if (s == "none")
            verify = Configuration::NONE;
        else if (s == "first")
            verify = Configuration::FIRST;
        else if (s == "all")
            verify = Configuration::ALL;
        else
            throw std::runtime_error("Unexpected verification mode");
    }

    return in;
}

std::ostream &
operator<<(std::ostream & out, const Configuration::Verify & verify)
{
    std::ostream::sentry sentry(out);

    if (sentry)
        switch (verify)
        {
        default:
        case Configuration::NONE:
            return out << "none";
        case Configuration::FIRST:
            return out << "first";
        case Configuration::ALL:
            return out << "all";
        }
}

std::ostream &
operator<<(std::ostream & out, const Configuration::Mode & mode)
{
    std::ostream::sentry sentry(out);

    if (sentry)
        switch (mode)
        {
        default:
        case Configuration::CLIENT:
            return out << "client";
        case Configuration::SERVER:
            return out << "server";
        }
}

std::ostream &
operator<<(std::ostream & out, const Configuration & configuration)
{
    std::ostream::sentry sentry(out);

    if (sentry)
    {
        out << "mode: " << configuration.mode << "\n";
        out << "endpoint: " << configuration.endpoint << "\n";
        out << "send_bandwidth: "
            << configuration.send_bandwidth << "/s\n";
        out << "receive_bandwidth: "
            << configuration.receive_bandwidth << "/s\n";
        out << "bandwidth_sampling_frequency: "
            << configuration.bandwidth_sampling_frequency << "Hz\n";
        out << "verify: " << configuration.verify << "\n";
        if (configuration.windows != 0)
            out << "windows: " << configuration.windows << "\n";
        else
            out << "windows: default system value\n";
        out << "size: " << configuration.size << "\n";
        if (configuration.duration_margin.is_special())
            out << "duration_margin: default";
        else
            out << "duration_margin: " << configuration.duration_margin;
        out << std::flush;
    }

    return out;
}


} // namespace tcp_tester
} // namespace enyx

