/*
    This file is part of keccakminer.

    keccakminer is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    keccakminer is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with keccakminer.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <libdevcore/Common.h>
#include <libdevcore/Exceptions.h>
#include <libdevcore/Worker.h>

#include <ethash/ethash.hpp>

namespace dev
{
namespace etc
{
struct Result
{
    h256 value;
};

class KeccakAux
{
public:
    static Result eval(h256 const& _headerHash, uint64_t _nonce) noexcept;
};

struct EpochContext
{
    int epochNumber;
    int lightNumItems;
    size_t lightSize;
    const ethash_hash512* lightCache;
    int dagNumItems;
    uint64_t dagSize;
};

struct WorkPackage
{
    WorkPackage() = default;

    explicit operator bool() const { return header != h256(); }

    std::string job;  // Job identifier can be anything. Not necessarily a hash

    h256 boundary;
    h256 header;  ///< When h256() means "pause until notified a new work package is available".
    h256 seed;

    int epoch = -1;
    int block = -1;

    uint64_t startNonce = 0;
    uint16_t exSizeBytes = 0;

    std::string algo = "ethash";
};

struct Solution
{
    uint64_t nonce;                                // Solution found nonce
    h256 mixHash;                                  // Mix hash
    WorkPackage work;                              // WorkPackage this solution refers to
    std::chrono::steady_clock::time_point tstamp;  // Timestamp of found solution
    unsigned midx;                                 // Originating miner Id
};

}  // namespace etc
}  // namespace dev
