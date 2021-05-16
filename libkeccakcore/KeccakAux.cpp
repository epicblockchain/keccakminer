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

#include "KeccakAux.h"

#include <ethash/ethash.hpp>
#include <ethash/keccak.hpp>

using namespace dev;
using namespace etc;

Result KeccakAux::eval(h256 const& _headerHash, uint64_t _nonce) noexcept
{
    std::array<byte, 40> header;
    std::array<byte, 8> nonce;

    header.fill(0);
    nonce.fill(0);
    
    toBigEndian(_nonce, nonce);

    memcpy(header.data(), _headerHash.data(), 32);
    memcpy(header.data() + 32, nonce.data(), 8);
    auto result = ethash::keccak256(header.data(), 40);
    h256 final{reinterpret_cast<byte*>(result.bytes), h256::ConstructFromPointer};
    return {final};
}