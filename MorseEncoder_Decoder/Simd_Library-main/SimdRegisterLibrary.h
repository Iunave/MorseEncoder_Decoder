/*
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

//If you make any additons and/or improvements please make a pull request for it!

#pragma once

#include <tiff.h>
#include <iostream>
#include <immintrin.h>

#ifndef ENABLE_CHECKS
#define ENABLE_CHECKS true
#endif

#ifndef likely
#define likely(expr) (__builtin_expect((expr), true))
#endif

#ifndef unlikely
#define unlikely(expr) (__builtin_expect((expr), false))
#endif

#define MoveTemp(target) reinterpret_cast<decltype(target)&&>(target)

#ifndef checkf
#define checkf(expr, message) \
do \
{ \
    if constexpr(ENABLE_CHECKS) \
    { \
        if unlikely(!(expr)) \
        { \
            std::cerr << "Line: " << __LINE__ << "\n" << "In file: " << __FILE__ << "\nMessage: " << message << std::endl; \
            std::abort(); \
        } \
    } \
} \
while(false);
#endif

#ifndef check
#define check(expr) \
do \
{ \
    if constexpr(ENABLE_CHECKS) \
    { \
        if unlikely(!(expr)) \
        { \
            std::cerr << "Line: " << __LINE__ << "\n" << "In file: " << __FILE__ << std::endl; \
            std::abort(); \
        } \
    } \
} \
while(false);
#endif

#ifndef TEXT
#define TEXT(text) text
#endif

#ifndef NODISCARD
#define NODISCARD [[nodiscard]]
#endif

#ifndef INLINE
#define INLINE inline __attribute__((always_inline))
#endif

#ifndef SIMD_ENABLE
#define SIMD_ENABLE true
#endif

using float32 = float;
using float64 = double;

#if SIMD_ENABLE

namespace Simd
{

    namespace Private
    {

        template<typename T>
        struct Element
        {
        };

        template<typename T> using ElementType = typename Element<T>::Type;

        template<>
        struct Element<__m128>
        {
            using Type = float32;
        };

        template<>
        struct Element<__m128d>
        {
            using Type = float64;
        };

        template<>
        struct Element<__v2du>
        {
            using Type = uint64;
        };

        template<>
        struct Element<__v2di>
        {
            using Type = int64;
        };

        template<>
        struct Element<__v4su>
        {
            using Type = uint32;
        };

        template<>
        struct Element<__v4si>
        {
            using Type = int32;
        };

        template<>
        struct Element<__v8hu>
        {
            using Type = uint16;
        };

        template<>
        struct Element<__v8hi>
        {
            using Type = int16;
        };

        template<>
        struct Element<__v16qu>
        {
            using Type = uint8;
        };

        template<>
        struct Element<__v16qi>
        {
            using Type = int8;
        };

#if __AVX__
        
        template<>
        struct Element<__m256>
        {
            using Type = float32;
        };

        template<>
        struct Element<__m256d>
        {
            using Type = float64;
        };

        template<>
        struct Element<__v4du>
        {
            using Type = uint64;
        };

        template<>
        struct Element<__v4di>
        {
            using Type = int64;
        };

        template<>
        struct Element<__v8su>
        {
            using Type = uint32;
        };

        template<>
        struct Element<__v8si>
        {
            using Type = int32;
        };

        template<>
        struct Element<__v16hu>
        {
            using Type = uint16;
        };

        template<>
        struct Element<__v16hi>
        {
            using Type = int16;
        };

        template<>
        struct Element<__v32qu>
        {
            using Type = uint8;
        };

        template<>
        struct Element<__v32qi>
        {
            using Type = int8;
        };

#endif //__AVX__
        
        template<typename RegisterType>
        class TVectorRegister;

        template<typename RegisterType>
        struct Element<TVectorRegister<RegisterType>>
        {
            using Type = ElementType<RegisterType>;
        };

    }

    inline constexpr uint8 Equal{0x00};
    inline constexpr uint8 Greater{0x0E};
    inline constexpr uint8 GreaterOrEqual{0x0D};
    inline constexpr uint8 Less{0x11};
    inline constexpr uint8 LessOrEqual{0x12};

#pragma mark Divide

    template<typename RegisterType>
    RegisterType Divide(const RegisterType&, const RegisterType&);

    template<>
    inline __m128 Divide(const __m128& LHS, const __m128& RHS)
    {
        return _mm_div_ps(LHS, RHS);
    }

    template<>
    inline __m128d Divide(const __m128d&  LHS, const __m128d& RHS)
    {
        return _mm_div_pd(LHS, RHS);
    }

#if __AVX__
    
    template<>
    inline __m256 Divide(const __m256& LHS, const __m256& RHS)
    {
        return _mm256_div_ps(LHS, RHS);
    }

    template<>
    inline __m256d Divide(const __m256d& LHS, const __m256d& RHS)
    {
        return _mm256_div_pd(LHS, RHS);
    }

#if __AVX2__
    
    template<>
    inline __v4du Divide(const __v4du& LHS, const __v4du& RHS)
    {
        checkf(false, TEXT("Not supported"))
        return __v4du{};
    }

    template<>
    inline __v4di Divide(const __v4di& LHS, const __v4di& RHS)
    {
        checkf(false, TEXT("Not supported"))
        return __v4di{};
    }

    template<>
    inline __v8su Divide(const __v8su& LHS, const __v8su& RHS)
    {
        checkf(false, TEXT("Not supported"))
        return __v4di{};
    }

    template<>
    inline __v8si Divide(const __v8si& LHS, const __v8si& RHS)
    {
        checkf(false, TEXT("Not supported"))
        return __v4di{};
    }

    template<>
    inline __v16hu Divide(const __v16hu& LHS, const __v16hu& RHS)
    {
        checkf(false, TEXT("Not supported"))
        return __v16hi{};
    }

    template<>
    inline __v16hi Divide(const __v16hi& LHS, const __v16hi& RHS)
    {
        checkf(false, TEXT("Not supported"))
        return __v16hi{};
    }

    template<>
    inline __v32qu Divide(const __v32qu& LHS, const __v32qu& RHS)
    {
        checkf(false, TEXT("Not supported"))
        return __v32qu{};
    }

    template<>
    inline __v32qi Divide(const __v32qi& LHS, const __v32qi& RHS)
    {
        checkf(false, TEXT("Not supported"))
        return __v32qi{};
    }

#endif //__AVX__
#endif //__AVX2__
    
    template<>
    inline __v2du Divide(const __v2du& LHS, const __v2du& RHS)
    {
        checkf(false, TEXT("Not supported"))
        return __v2du{};
    }

    template<>
    inline __v2di Divide(const __v2di& LHS, const __v2di& RHS)
    {
        checkf(false, TEXT("Not supported"))
        return __v2di{};
    }

    template<>
    inline __v4su Divide(const __v4su& LHS, const __v4su& RHS)
    {
        checkf(false, TEXT("Not supported"))
        return __v4su{};
    }

    template<>
    inline __v4si Divide(const __v4si& LHS, const __v4si& RHS)
    {
        checkf(false, TEXT("Not supported"))
        return __v4si{};
    }

    template<>
    inline __v8hu Divide(const __v8hu& LHS, const __v8hu& RHS)
    {
        checkf(false, TEXT("Not supported"))
        return __v8hu{};
    }

    template<>
    inline __v8hi Divide(const __v8hi& LHS, const __v8hi& RHS)
    {
        checkf(false, TEXT("Not supported"))
        return __v8hi{};
    }

    template<>
    inline __v16qu Divide(const __v16qu& LHS, const __v16qu& RHS)
    {
        checkf(false, TEXT("Not supported"))
        return __v16qu{};
    }

    template<>
    inline __v16qi Divide(const __v16qi& LHS, const __v16qi& RHS)
    {
        checkf(false, TEXT("Not supported"))
        return __v16qi{};
    }

#pragma mark Add

    template<typename RegisterType>
    RegisterType Add(const RegisterType&, const RegisterType&);

    template<>
    inline __m128 Add(const __m128& LHS, const __m128& RHS)
    {
        return _mm_add_ps(LHS, RHS);
    }

    template<>
    inline __m128d Add(const __m128d& LHS, const __m128d& RHS)
    {
        return _mm_add_pd(LHS, RHS);
    }

#if __AVX__
    
    template<>
    inline __m256 Add(const __m256& LHS, const __m256& RHS)
    {
        return _mm256_add_ps(LHS, RHS);
    }

    template<>
    inline __m256d Add(const __m256d& LHS, const __m256d& RHS)
    {
        return _mm256_add_pd(LHS, RHS);
    }

#if __AVX2__
    
    template<>
    inline __v4du Add(const __v4du& LHS, const __v4du& RHS)
    {
        return _mm256_add_epi64(LHS, RHS);
    }

    template<>
    inline __v4di Add(const __v4di& LHS, const __v4di& RHS)
    {
        return _mm256_add_epi64(LHS, RHS);
    }

    template<>
    inline __v8su Add(const __v8su& LHS, const __v8su& RHS)
    {
        return _mm256_add_epi32(LHS, RHS);
    }

    template<>
    inline __v8si Add(const __v8si& LHS, const __v8si& RHS)
    {
        return _mm256_add_epi32(LHS, RHS);
    }

    template<>
    inline __v16hu Add(const __v16hu& LHS, const __v16hu& RHS)
    {
        return _mm256_add_epi16(LHS, RHS);
    }

    template<>
    inline __v16hi Add(const __v16hi& LHS, const __v16hi& RHS)
    {
        return _mm256_add_epi16(LHS, RHS);
    }

    template<>
    inline __v32qu Add(const __v32qu& LHS, const __v32qu& RHS)
    {
        return _mm256_add_epi8(LHS, RHS);
    }

    template<>
    inline __v32qi Add(const __v32qi& LHS, const __v32qi& RHS)
    {
        return _mm256_add_epi8(LHS, RHS);
    }

#endif //__AVX__
#endif //__AVX2__
    
    template<>
    inline __v2du Add(const __v2du& LHS, const __v2du& RHS)
    {
        return _mm_add_epi64(LHS, RHS);
    }

    template<>
    inline __v2di Add(const __v2di& LHS, const __v2di& RHS)
    {
        return _mm_add_epi64(LHS, RHS);
    }

    template<>
    inline __v4su Add(const __v4su& LHS, const __v4su& RHS)
    {
        return _mm_add_epi32(LHS, RHS);
    }

    template<>
    inline __v4si Add(const __v4si& LHS, const __v4si& RHS)
    {
        return _mm_add_epi32(LHS, RHS);
    }

    template<>
    inline __v8hu Add(const __v8hu& LHS, const __v8hu& RHS)
    {
        return _mm_add_epi16(LHS, RHS);
    }

    template<>
    inline __v8hi Add(const __v8hi& LHS, const __v8hi& RHS)
    {
        return _mm_add_epi16(LHS, RHS);
    }

    template<>
    inline __v16qu Add(const __v16qu& LHS, const __v16qu& RHS)
    {
        return _mm_add_epi8(LHS, RHS);
    }

    template<>
    inline __v16qi Add(const __v16qi& LHS, const __v16qi& RHS)
    {
        return _mm_add_epi8(LHS, RHS);
    }

#pragma mark Subract

    template<typename RegisterType>
    RegisterType Subtract(const RegisterType&, const RegisterType&);

    template<>
    inline __m128 Subtract(const __m128& LHS, const __m128& RHS)
    {
        return _mm_sub_ps(LHS, RHS);
    }

    template<>
    inline __m128d Subtract(const __m128d& LHS, const __m128d& RHS)
    {
        return _mm_sub_pd(LHS, RHS);
    }

#if __AVX__
    
    template<>
    inline __m256 Subtract(const __m256& LHS, const __m256& RHS)
    {
        return _mm256_sub_ps(LHS, RHS);
    }

    template<>
    inline __m256d Subtract(const __m256d& LHS, const __m256d& RHS)
    {
        return _mm256_sub_pd(LHS, RHS);
    }

#if __AVX2__
    
    template<>
    inline __v4du Subtract(const __v4du& LHS, const __v4du& RHS)
    {
        return _mm256_sub_epi64(LHS, RHS);
    }

    template<>
    inline __v4di Subtract(const __v4di& LHS, const __v4di& RHS)
    {
        return _mm256_sub_epi64(LHS, RHS);
    }

    template<>
    inline __v8su Subtract(const __v8su& LHS, const __v8su& RHS)
    {
        return _mm256_sub_epi32(LHS, RHS);
    }

    template<>
    inline __v8si Subtract(const __v8si& LHS, const __v8si& RHS)
    {
        return _mm256_sub_epi32(LHS, RHS);
    }

    template<>
    inline __v16hu Subtract(const __v16hu& LHS, const __v16hu& RHS)
    {
        return _mm256_sub_epi16(LHS, RHS);
    }

    template<>
    inline __v16hi Subtract(const __v16hi& LHS, const __v16hi& RHS)
    {
        return _mm256_sub_epi16(LHS, RHS);
    }

    template<>
    inline __v32qu Subtract(const __v32qu& LHS, const __v32qu& RHS)
    {
        return _mm256_sub_epi8(LHS, RHS);
    }

    template<>
    inline __v32qi Subtract(const __v32qi& LHS, const __v32qi& RHS)
    {
        return _mm256_sub_epi8(LHS, RHS);
    }

#endif //__AVX__
#endif //__AVX2__
    
    template<>
    inline __v2du Subtract(const __v2du& LHS, const __v2du& RHS)
    {
        return _mm_sub_epi64(LHS, RHS);
    }

    template<>
    inline __v2di Subtract(const __v2di& LHS, const __v2di& RHS)
    {
        return _mm_sub_epi64(LHS, RHS);
    }

    template<>
    inline __v4su Subtract(const __v4su& LHS, const __v4su& RHS)
    {
        return _mm_sub_epi32(LHS, RHS);
    }

    template<>
    inline __v4si Subtract(const __v4si& LHS, const __v4si& RHS)
    {
        return _mm_sub_epi32(LHS, RHS);
    }

    template<>
    inline __v8hu Subtract(const __v8hu& LHS, const __v8hu& RHS)
    {
        return _mm_sub_epi16(LHS, RHS);
    }

    template<>
    inline __v8hi Subtract(const __v8hi& LHS, const __v8hi& RHS)
    {
        return _mm_sub_epi16(LHS, RHS);
    }

    template<>
    inline __v16qu Subtract(const __v16qu& LHS, const __v16qu& RHS)
    {
        return _mm_sub_epi8(LHS, RHS);
    }

    template<>
    inline __v16qi Subtract(const __v16qi& LHS, const __v16qi& RHS)
    {
        return _mm_sub_epi8(LHS, RHS);
    }

#pragma mark Multiply

    template<typename RegisterType>
    RegisterType Multiply(const RegisterType&, const RegisterType&);

    template<>
    inline __m128 Multiply(const __m128& LHS, const __m128& RHS)
    {
        return _mm_mul_ps(LHS, RHS);
    }

    template<>
    inline __m128d Multiply(const __m128d& LHS, const __m128d& RHS)
    {
        return _mm_mul_pd(LHS, RHS);
    }

#if __AVX__
    
    template<>
    inline __m256 Multiply(const __m256& LHS, const __m256& RHS)
    {
        return _mm256_mul_ps(LHS, RHS);
    }

    template<>
    inline __m256d Multiply(const __m256d& LHS, const __m256d& RHS)
    {
        return _mm256_mul_pd(LHS, RHS);
    }

#if __AVX2__
    
    template<>
    inline __v4du Multiply(const __v4du& LHS, const __v4du& RHS)
    {
        checkf(false, TEXT("Not supported"))
        return __v4du{0};
    }

    template<>
    inline __v4di Multiply(const __v4di& LHS, const __v4di& RHS)
    {
        checkf(false, TEXT("Not supported"))
        return __v4di{0};
    }

    template<>
    inline __v8su Multiply(const __v8su& LHS, const __v8su& RHS)
    {
        return _mm256_mul_epu32(LHS, RHS);
    }

    template<>
    inline __v8si Multiply(const __v8si& LHS, const __v8si& RHS)
    {
        return _mm256_mul_epi32(LHS, RHS);
    }

    template<>
    inline __v16hu Multiply(const __v16hu& LHS, const __v16hu& RHS)
    {
        return _mm256_mullo_epi16(LHS, RHS);
    }

    template<>
    inline __v16hi Multiply(const __v16hi& LHS, const __v16hi& RHS)
    {
        return _mm256_mullo_epi16(LHS, RHS);
    }

    template<>
    inline __v32qu Multiply(const __v32qu& LHS, const __v32qu& RHS)
    {
        checkf(false, TEXT("Not supported"))
        return __v32qu{};
    }

    template<>
    inline __v32qi Multiply(const __v32qi& LHS, const __v32qi& RHS)
    {
        checkf(false, TEXT("Not supported"))
        return __v32qi{};
    }

#endif //__AVX__
#endif //__AVX2__
    
    template<>
    inline __v2du Multiply(const __v2du& LHS, const __v2du& RHS)
    {
        return __m128i{static_cast<int64>(LHS[0] * RHS[0]), static_cast<int64>(LHS[1] * RHS[1])};
    }

    template<>
    inline __v2di Multiply(const __v2di& LHS, const __v2di& RHS)
    {
        return __m128i{static_cast<int64>(LHS[0] * RHS[0]), static_cast<int64>(LHS[1] * RHS[1])};
    }

    template<>
    inline __v4su Multiply(const __v4su& LHS, const __v4su& RHS)
    {
        return _mm_mullo_epi32(LHS, RHS);
    }

    template<>
    inline __v4si Multiply(const __v4si& LHS, const __v4si& RHS)
    {
        return _mm_mullo_epi32(LHS, RHS);
    }

    template<>
    inline __v8hu Multiply(const __v8hu& LHS, const __v8hu& RHS)
    {
        return _mm_mullo_epi16(LHS, RHS);
    }

    template<>
    inline __v8hi Multiply(const __v8hi& LHS, const __v8hi& RHS)
    {
        return _mm_mullo_epi16(LHS, RHS);
    }

    template<>
    inline __v16qu Multiply(const __v16qu& LHS, const __v16qu& RHS)
    {
        checkf(false, TEXT("Not supported"))
        return __v16qu{0};
    }

    template<>
    inline __v16qi Multiply(const __v16qi& LHS, const __v16qi& RHS)
    {
        checkf(false, TEXT("Not supported"))
        return __v16qi{0};
    }

#pragma mark Set1

    template<typename RegisterType>
    RegisterType SetAllFromOne(Private::ElementType<RegisterType>);

    template<>
    inline __m128 SetAllFromOne(const Private::ElementType<__m128> Value)
    {
        return _mm_set1_ps(Value);
    }

    template<>
    inline __m128d SetAllFromOne(const Private::ElementType<__m128d> Value)
    {
        return _mm_set1_pd(Value);
    }

#if __AVX__
    
    template<>
    inline __m256 SetAllFromOne(const Private::ElementType<__m256> Value)
    {
        return _mm256_set1_ps(Value);
    }

    template<>
    inline __m256d SetAllFromOne(const Private::ElementType<__m256d> Value)
    {
        return _mm256_set1_pd(Value);
    }

    template<>
    inline __v4du SetAllFromOne(const Private::ElementType<__v4du> Value)
    {
        return _mm256_set1_epi64x(Value);
    }

    template<>
    inline __v4di SetAllFromOne(const Private::ElementType<__v4di> Value)
    {
        return _mm256_set1_epi64x(Value);
    }

    template<>
    inline __v8su SetAllFromOne(const Private::ElementType<__v8su> Value)
    {
        return _mm256_set1_epi32(Value);
    }

    template<>
    inline __v8si SetAllFromOne(const Private::ElementType<__v8si> Value)
    {
        return _mm256_set1_epi32(Value);
    }

    template<>
    inline __v16hu SetAllFromOne(const Private::ElementType<__v16hu> Value)
    {
        return _mm256_set1_epi16(Value);
    }

    template<>
    inline __v16hi SetAllFromOne(const Private::ElementType<__v16hi> Value)
    {
        return _mm256_set1_epi16(Value);
    }

    template<>
    inline __v32qu SetAllFromOne(const Private::ElementType<__v32qu> Value)
    {
        return _mm256_set1_epi8(Value);
    }

    template<>
    inline __v32qi SetAllFromOne(const Private::ElementType<__v32qi> Value)
    {
        return _mm256_set1_epi8(Value);
    }

#endif //__AVX__
    
    template<>
    inline __v2du SetAllFromOne(const Private::ElementType<__v2du> Value)
    {
        return _mm_set1_epi64x(Value);
    }

    template<>
    inline __v2di SetAllFromOne(const Private::ElementType<__v2di> Value)
    {
        return _mm_set1_epi64x(Value);
    }

    template<>
    inline __v4su SetAllFromOne(const Private::ElementType<__v4su> Value)
    {
        return _mm_set1_epi32(Value);
    }

    template<>
    inline __v4si SetAllFromOne(const Private::ElementType<__v4si> Value)
    {
        return _mm_set1_epi32(Value);
    }

    template<>
    inline __v8hu SetAllFromOne(const Private::ElementType<__v8hu> Value)
    {
        return _mm_set1_epi16(Value);
    }

    template<>
    inline __v8hi SetAllFromOne(const Private::ElementType<__v8hi> Value)
    {
        return _mm_set1_epi16(Value);
    }

    template<>
    inline __v16qu SetAllFromOne(const Private::ElementType<__v16qu> Value)
    {
        return _mm_set1_epi8(Value);
    }

    template<>
    inline __v16qi SetAllFromOne(const Private::ElementType<__v16qi> Value)
    {
        return _mm_set1_epi8(Value);
    }

#pragma mark CompareEqual

    template<typename RegisterType>
    bool CompareEqual(const RegisterType&, const RegisterType&);

#if __AVX__
    
    template<>
    inline bool CompareEqual(const __m128& LHS, const __m128& RHS)
    {
        return _mm_movemask_ps(_mm_cmp_ps(LHS, RHS, Equal)) == (int)0b00000000000000000000000000001111;
    }

    template<>
    inline bool CompareEqual(const __m128d& LHS, const __m128d& RHS)
    {
        return _mm_movemask_pd(_mm_cmp_pd(LHS, RHS, Equal)) == (int)0b000000000000000000000000000011;
    }

    template<>
    inline bool CompareEqual(const __m256& LHS, const __m256& RHS)
    {
        return _mm256_movemask_ps(_mm256_cmp_ps(LHS, RHS, Equal)) == (int)0b00000000000000000000000011111111;
    }

    template<>
    inline bool CompareEqual(const __m256d& LHS, const __m256d& RHS)
    {
        return _mm256_movemask_pd(_mm256_cmp_pd(LHS, RHS, Equal)) == (int)0b00000000000000000000000000001111;
    }

#if __AVX2__
    
    template<>
    inline bool CompareEqual(const __v4du& LHS, const __v4du& RHS)
    {
        return _mm256_movemask_epi8(_mm256_cmpeq_epi64(LHS, RHS)) == (int)0b11111111111111111111111111111111;
    }

    template<>
    inline bool CompareEqual(const __v4di& LHS, const __v4di& RHS)
    {
        return _mm256_movemask_epi8(_mm256_cmpeq_epi64(LHS, RHS)) == (int)0b11111111111111111111111111111111;
    }

    template<>
    inline bool CompareEqual(const __v8su& LHS, const __v8su& RHS)
    {
        return _mm256_movemask_epi8(_mm256_cmpeq_epi32(LHS, RHS)) == (int)0b11111111111111111111111111111111;
    }

    template<>
    inline bool CompareEqual(const __v8si& LHS, const __v8si& RHS)
    {
        return _mm256_movemask_epi8(_mm256_cmpeq_epi32(LHS, RHS)) == (int)0b11111111111111111111111111111111;
    }

    template<>
    inline bool CompareEqual(const __v16hu& LHS, const __v16hu& RHS)
    {
        return _mm256_movemask_epi8(_mm256_cmpeq_epi16(LHS, RHS)) == (int)0b11111111111111111111111111111111;
    }

    template<>
    inline bool CompareEqual(const __v16hi& LHS, const __v16hi& RHS)
    {
        return _mm256_movemask_epi8(_mm256_cmpeq_epi16(LHS, RHS)) == (int)0b11111111111111111111111111111111;
    }

    template<>
    inline bool CompareEqual(const __v32qu& LHS, const __v32qu& RHS)
    {
        return _mm256_movemask_epi8(_mm256_cmpeq_epi8(LHS, RHS)) == (int)0b11111111111111111111111111111111;
    }

    template<>
    inline bool CompareEqual(const __v32qi& LHS, const __v32qi& RHS)
    {
        return _mm256_movemask_epi8(_mm256_cmpeq_epi8(LHS, RHS)) == (int)0b11111111111111111111111111111111;
    }

#endif //__AVX__
#endif //__AVX2__
    
    template<>
    inline bool CompareEqual(const __v2du& LHS, const __v2du& RHS)
    {
        return _mm_movemask_epi8(_mm_cmpeq_epi64(LHS, RHS)) == (int)0b00000000000000001111111111111111;
    }

    template<>
    inline bool CompareEqual(const __v2di& LHS, const __v2di& RHS)
    {
        return _mm_movemask_epi8(_mm_cmpeq_epi64(LHS, RHS)) == (int)0b00000000000000001111111111111111;
    }

    template<>
    inline bool CompareEqual(const __v4su& LHS, const __v4su& RHS)
    {
        return _mm_movemask_epi8(_mm_cmpeq_epi32(LHS, RHS)) == (int)0b00000000000000001111111111111111;
    }

    template<>
    inline bool CompareEqual(const __v4si& LHS, const __v4si& RHS)
    {
        return _mm_movemask_epi8(_mm_cmpeq_epi32(LHS, RHS)) == (int)0b00000000000000001111111111111111;
    }

    template<>
    inline bool CompareEqual(const __v8hu& LHS, const __v8hu& RHS)
    {
        return _mm_movemask_epi8(_mm_cmpeq_epi16(LHS, RHS)) == (int)0b00000000000000001111111111111111;
    }

    template<>
    inline bool CompareEqual(const __v8hi& LHS, const __v8hi& RHS)
    {
        return _mm_movemask_epi8(_mm_cmpeq_epi16(LHS, RHS)) == (int)0b00000000000000001111111111111111;
    }

    template<>
    inline bool CompareEqual(const __v16qu& LHS, const __v16qu& RHS)
    {
        return _mm_movemask_epi8(_mm_cmpeq_epi16(LHS, RHS)) == (int)0b00000000000000001111111111111111;
    }

    template<>
    inline bool CompareEqual(const __v16qi& LHS, const __v16qi& RHS)
    {
        return _mm_movemask_epi8(_mm_cmpeq_epi8(LHS, RHS)) == (int)0b00000000000000001111111111111111;
    }

#pragma mark CompareGreater

    template<typename RegisterType>
    bool CompareGreater(const RegisterType&, const RegisterType&);

#if __AVX__
    
    template<>
    inline bool CompareGreater(const __m128& LHS, const __m128& RHS)
    {
        return _mm_movemask_ps(_mm_cmp_ps(LHS, RHS, Greater)) == (int)0b00000000000000000000000000001111;
    }

    template<>
    inline bool CompareGreater(const __m128d& LHS, const __m128d& RHS)
    {
        return _mm_movemask_pd(_mm_cmp_pd(LHS, RHS, Greater)) == (int)0b000000000000000000000000000011;
    }

    template<>
    inline bool CompareGreater(const __m256& LHS, const __m256& RHS)
    {
        return _mm256_movemask_ps(_mm256_cmp_ps(LHS, RHS, Greater)) == (int)0b00000000000000000000000011111111;
    }

    template<>
    inline bool CompareGreater(const __m256d& LHS, const __m256d& RHS)
    {
        return _mm256_movemask_pd(_mm256_cmp_pd(LHS, RHS, Greater)) == (int)0b00000000000000000000000000001111;
    }

#if __AVX2__
    
    template<>
    inline bool CompareGreater(const __v4du& LHS, const __v4du& RHS)
    {
        return _mm256_movemask_epi8(_mm256_cmpgt_epi64(LHS, RHS)) == (int)0b11111111111111111111111111111111;
    }

    template<>
    inline bool CompareGreater(const __v4di& LHS, const __v4di& RHS)
    {
        return _mm256_movemask_epi8(_mm256_cmpgt_epi64(LHS, RHS)) == (int)0b11111111111111111111111111111111;
    }

    template<>
    inline bool CompareGreater(const __v8su& LHS, const __v8su& RHS)
    {
        return _mm256_movemask_epi8(_mm256_cmpgt_epi32(LHS, RHS)) == (int)0b11111111111111111111111111111111;
    }

    template<>
    inline bool CompareGreater(const __v8si& LHS, const __v8si& RHS)
    {
        return _mm256_movemask_epi8(_mm256_cmpgt_epi32(LHS, RHS)) == (int)0b11111111111111111111111111111111;
    }

    template<>
    inline bool CompareGreater(const __v16hu& LHS, const __v16hu& RHS)
    {
        return _mm256_movemask_epi8(_mm256_cmpgt_epi16(LHS, RHS)) == (int)0b11111111111111111111111111111111;
    }

    template<>
    inline bool CompareGreater(const __v16hi& LHS, const __v16hi& RHS)
    {
        return _mm256_movemask_epi8(_mm256_cmpgt_epi16(LHS, RHS)) == (int)0b11111111111111111111111111111111;
    }

    template<>
    inline bool CompareGreater(const __v32qu& LHS, const __v32qu& RHS)
    {
        return _mm256_movemask_epi8(_mm256_cmpgt_epi8(LHS, RHS)) == (int)0b11111111111111111111111111111111;
    }

    template<>
    inline bool CompareGreater(const __v32qi& LHS, const __v32qi& RHS)
    {
        return _mm256_movemask_epi8(_mm256_cmpgt_epi8(LHS, RHS)) == (int)0b11111111111111111111111111111111;
    }

#endif //__AVX__
#endif //__AVX2__
    
    template<>
    inline bool CompareGreater(const __v2du& LHS, const __v2du& RHS)
    {
        return _mm_movemask_epi8(_mm_cmpgt_epi64(LHS, RHS)) == (int)0b00000000000000001111111111111111;
    }

    template<>
    inline bool CompareGreater(const __v2di& LHS, const __v2di& RHS)
    {
        return _mm_movemask_epi8(_mm_cmpgt_epi64(LHS, RHS)) == (int)0b00000000000000001111111111111111;
    }

    template<>
    inline bool CompareGreater(const __v4su& LHS, const __v4su& RHS)
    {
        return _mm_movemask_epi8(_mm_cmpgt_epi32(LHS, RHS)) == (int)0b00000000000000001111111111111111;
    }

    template<>
    inline bool CompareGreater(const __v4si& LHS, const __v4si& RHS)
    {
        return _mm_movemask_epi8(_mm_cmpgt_epi32(LHS, RHS)) == (int)0b00000000000000001111111111111111;
    }

    template<>
    inline bool CompareGreater(const __v8hu& LHS, const __v8hu& RHS)
    {
        return _mm_movemask_epi8(_mm_cmpgt_epi16(LHS, RHS)) == (int)0b00000000000000001111111111111111;
    }

    template<>
    inline bool CompareGreater(const __v8hi& LHS, const __v8hi& RHS)
    {
        return _mm_movemask_epi8(_mm_cmpgt_epi16(LHS, RHS)) == (int)0b00000000000000001111111111111111;
    }

    template<>
    inline bool CompareGreater(const __v16qu& LHS, const __v16qu& RHS)
    {
        return _mm_movemask_epi8(_mm_cmpgt_epi16(LHS, RHS)) == (int)0b00000000000000001111111111111111;
    }

    template<>
    inline bool CompareGreater(const __v16qi& LHS, const __v16qi& RHS)
    {
        return _mm_movemask_epi8(_mm_cmpgt_epi8(LHS, RHS)) == (int)0b00000000000000001111111111111111;
    }

#pragma mark CompareGreaterOrEqual

    template<typename RegisterType>
    bool CompareGreaterOrEqual(const RegisterType&, const RegisterType&);

#if __AVX__
    
    template<>
    inline bool CompareGreaterOrEqual(const __m128& LHS, const __m128& RHS)
    {
        return _mm_movemask_ps(_mm_cmp_ps(LHS, RHS, GreaterOrEqual)) == (int)0b00000000000000000000000000001111;
    }

    template<>
    inline bool CompareGreaterOrEqual(const __m128d& LHS, const __m128d& RHS)
    {
        return _mm_movemask_pd(_mm_cmp_pd(LHS, RHS, GreaterOrEqual)) == (int)0b000000000000000000000000000011;
    }

    template<>
    inline bool CompareGreaterOrEqual(const __m256& LHS, const __m256& RHS)
    {
        return _mm256_movemask_ps(_mm256_cmp_ps(LHS, RHS, GreaterOrEqual)) == (int)0b00000000000000000000000011111111;
    }

    template<>
    inline bool CompareGreaterOrEqual(const __m256d& LHS, const __m256d& RHS)
    {
        return _mm256_movemask_pd(_mm256_cmp_pd(LHS, RHS, GreaterOrEqual)) == (int)0b00000000000000000000000000001111;
    }

#if __AVX2__
    
    template<>
    inline bool CompareGreaterOrEqual(const __v4du& LHS, const __v4du& RHS)
    {
        //no cmpge exists so subtract 1 from RHS
        return _mm256_movemask_epi8(_mm256_cmpgt_epi64(LHS, Subtract(RHS, SetAllFromOne<__v4du>(1)))) == (int)0b11111111111111111111111111111111;
    }

    template<>
    inline bool CompareGreaterOrEqual(const __v4di& LHS, const __v4di& RHS)
    {
        //no cmpge exists so subtract 1 from RHS
        return _mm256_movemask_epi8(_mm256_cmpgt_epi64(LHS, Subtract(RHS, SetAllFromOne<__v4di>(1)))) == (int)0b11111111111111111111111111111111;
    }

    template<>
    inline bool CompareGreaterOrEqual(const __v8su& LHS, const __v8su& RHS)
    {
        //no cmpge exists so subtract 1 from RHS
        return _mm256_movemask_epi8(_mm256_cmpgt_epi32(LHS, Subtract(RHS, SetAllFromOne<__v8su>(1)))) == (int)0b11111111111111111111111111111111;
    }

    template<>
    inline bool CompareGreaterOrEqual(const __v8si& LHS, const __v8si& RHS)
    {
        //no cmpge exists so subtract 1 from RHS
        return _mm256_movemask_epi8(_mm256_cmpgt_epi32(LHS, Subtract(RHS, SetAllFromOne<__v8si>(1)))) == (int)0b11111111111111111111111111111111;
    }

    template<>
    inline bool CompareGreaterOrEqual(const __v16hu& LHS, const __v16hu& RHS)
    {
        //no cmpge exists so subtract 1 from RHS
        return _mm256_movemask_epi8(_mm256_cmpgt_epi16(LHS, Subtract(RHS, SetAllFromOne<__v16hu>(1)))) == (int)0b11111111111111111111111111111111;
    }

    template<>
    inline bool CompareGreaterOrEqual(const __v16hi& LHS, const __v16hi& RHS)
    {
        //no cmpge exists so subtract 1 from RHS
        return _mm256_movemask_epi8(_mm256_cmpgt_epi16(LHS, Subtract(RHS, SetAllFromOne<__v16hi>(1)))) == (int)0b11111111111111111111111111111111;
    }

    template<>
    inline bool CompareGreaterOrEqual(const __v32qu& LHS, const __v32qu& RHS)
    {
        //no cmpge exists so subtract 1 from RHS
        return _mm256_movemask_epi8(_mm256_cmpgt_epi8(LHS, Subtract(RHS, SetAllFromOne<__v32qu>(1)))) == (int)0b11111111111111111111111111111111;
    }

    template<>
    inline bool CompareGreaterOrEqual(const __v32qi& LHS, const __v32qi& RHS)
    {
        //no cmpge exists so subtract 1 from RHS
        return _mm256_movemask_epi8(_mm256_cmpgt_epi8(LHS, Subtract(RHS, SetAllFromOne<__v32qi>(1)))) == (int)0b11111111111111111111111111111111;
    }

#endif //__AVX__
#endif //__AVX2__
    
    template<>
    inline bool CompareGreaterOrEqual(const __v2du& LHS, const __v2du& RHS)
    {
        //no cmpge exists so subtract 1 from RHS
        return _mm_movemask_epi8(_mm_cmpgt_epi64(LHS, Subtract(RHS, SetAllFromOne<__v2du>(1)))) == (int)0b00000000000000001111111111111111;
    }

    template<>
    inline bool CompareGreaterOrEqual(const __v2di& LHS, const __v2di& RHS)
    {
        //no cmpge exists so subtract 1 from RHS
        return _mm_movemask_epi8(_mm_cmpgt_epi64(LHS, Subtract(RHS, SetAllFromOne<__v2di>(1)))) == (int)0b00000000000000001111111111111111;
    }

    template<>
    inline bool CompareGreaterOrEqual(const __v4su& LHS, const __v4su& RHS)
    {
        //no cmpge exists so subtract 1 from RHS
        return _mm_movemask_epi8(_mm_cmpgt_epi32(LHS, Subtract(RHS, SetAllFromOne<__v4su>(1)))) == (int)0b00000000000000001111111111111111;
    }

    template<>
    inline bool CompareGreaterOrEqual(const __v4si& LHS, const __v4si& RHS)
    {
        //no cmpge exists so subtract 1 from RHS
        return _mm_movemask_epi8(_mm_cmpgt_epi32(LHS, Subtract(RHS, SetAllFromOne<__v4si>(1)))) == (int)0b00000000000000001111111111111111;
    }

    template<>
    inline bool CompareGreaterOrEqual(const __v8hu& LHS, const __v8hu& RHS)
    {
        //no cmpge exists so subtract 1 from RHS
        return _mm_movemask_epi8(_mm_cmpgt_epi16(LHS, Subtract(RHS, SetAllFromOne<__v8hu>(1)))) == (int)0b00000000000000001111111111111111;
    }

    template<>
    inline bool CompareGreaterOrEqual(const __v8hi& LHS, const __v8hi& RHS)
    {
        //no cmpge exists so subtract 1 from RHS
        return _mm_movemask_epi8(_mm_cmpgt_epi16(LHS, Subtract(RHS, SetAllFromOne<__v8hi>(1)))) == (int)0b00000000000000001111111111111111;
    }

    template<>
    inline bool CompareGreaterOrEqual(const __v16qu& LHS, const __v16qu& RHS)
    {
        //no cmpge exists so subtract 1 from RHS
        return _mm_movemask_epi8(_mm_cmpgt_epi8(LHS, Subtract(RHS, SetAllFromOne<__v16qu>(1)))) == (int)0b00000000000000001111111111111111;
    }

    template<>
    inline bool CompareGreaterOrEqual(const __v16qi& LHS, const __v16qi& RHS)
    {
        //no cmpge exists so subtract 1 from RHS
        return _mm_movemask_epi8(_mm_cmpgt_epi8(LHS, Subtract(RHS, SetAllFromOne<__v16qi>(1)))) == (int)0b00000000000000001111111111111111;
    }

#pragma mark CompareLess

    template<typename RegisterType>
    bool CompareLess(const RegisterType&, const RegisterType&);

#if __AVX__
    
    template<>
    inline bool CompareLess(const __m128& LHS, const __m128& RHS)
    {
        return _mm_movemask_ps(_mm_cmp_ps(LHS, RHS, Less)) == (int)0b00000000000000000000000000001111;
    }

    template<>
    inline bool CompareLess(const __m128d& LHS, const __m128d& RHS)
    {
        return _mm_movemask_pd(_mm_cmp_pd(LHS, RHS, Less)) == (int)0b000000000000000000000000000011;
    }

    template<>
    inline bool CompareLess(const __m256& LHS, const __m256& RHS)
    {
        return _mm256_movemask_ps(_mm256_cmp_ps(LHS, RHS, Less)) == (int)0b00000000000000000000000011111111;
    }

    template<>
    inline bool CompareLess(const __m256d& LHS, const __m256d& RHS)
    {
        return _mm256_movemask_pd(_mm256_cmp_pd(LHS, RHS, Less)) == (int)0b00000000000000000000000000001111;
    }

#if __AVX2__
    
    template<>
    inline bool CompareLess(const __v4du& LHS, const __v4du& RHS)
    {
        //swap the order of parameters so we see if RHS is greater than LHS
        return _mm256_movemask_epi8(_mm256_cmpgt_epi64(RHS, LHS)) == (int)0b11111111111111111111111111111111;
    }

    template<>
    inline bool CompareLess(const __v4di& LHS, const __v4di& RHS)
    {
        //swap the order of parameters so we see if RHS is greater than LHS
        return _mm256_movemask_epi8(_mm256_cmpgt_epi64(RHS, LHS)) == (int)0b11111111111111111111111111111111;
    }

    template<>
    inline bool CompareLess(const __v8su& LHS, const __v8su& RHS)
    {
        //swap the order of parameters so we see if RHS is greater than LHS
        return _mm256_movemask_epi8(_mm256_cmpgt_epi32(RHS, LHS)) == (int)0b11111111111111111111111111111111;
    }

    template<>
    inline bool CompareLess(const __v8si& LHS, const __v8si& RHS)
    {
        //swap the order of parameters so we see if RHS is greater than LHS
        return _mm256_movemask_epi8(_mm256_cmpgt_epi32(RHS, LHS)) == (int)0b11111111111111111111111111111111;
    }

    template<>
    inline bool CompareLess(const __v16hu& LHS, const __v16hu& RHS)
    {
        //swap the order of parameters so we see if RHS is greater than LHS
        return _mm256_movemask_epi8(_mm256_cmpgt_epi16(RHS, LHS)) == (int)0b11111111111111111111111111111111;
    }

    template<>
    inline bool CompareLess(const __v16hi& LHS, const __v16hi& RHS)
    {
        //swap the order of parameters so we see if RHS  is greater than LHS
        return _mm256_movemask_epi8(_mm256_cmpgt_epi16(RHS, LHS)) == (int)0b11111111111111111111111111111111;
    }

    template<>
    inline bool CompareLess(const __v32qu& LHS, const __v32qu& RHS)
    {
        //swap the order of parameters so we see if RHS is greater than LHS
        return _mm256_movemask_epi8(_mm256_cmpgt_epi8(RHS, LHS)) == (int)0b11111111111111111111111111111111;
    }

    template<>
    inline bool CompareLess(const __v32qi& LHS, const __v32qi& RHS)
    {
        //swap the order of parameters so we see if RHS is greater than LHS
        return _mm256_movemask_epi8(_mm256_cmpgt_epi8(RHS, LHS)) == (int)0b11111111111111111111111111111111;
    }

#endif //__AVX__
#endif //__AVX2__
    
    template<>
    inline bool CompareLess(const __v2du& LHS, const __v2du& RHS)
    {
        //swap the order of parameters so we see if RHS is greater than LHS
        return _mm_movemask_epi8(_mm_cmpgt_epi64(RHS, LHS)) == (int)0b00000000000000001111111111111111;
    }

    template<>
    inline bool CompareLess(const __v2di& LHS, const __v2di& RHS)
    {
        return _mm_movemask_epi8(_mm_cmplt_epi32(LHS, RHS)) == (int)0b00000000000000001111111111111111;
    }

    template<>
    inline bool CompareLess(const __v4su& LHS, const __v4su& RHS)
    {
        return _mm_movemask_epi8(_mm_cmplt_epi32(LHS, RHS)) == (int)0b00000000000000001111111111111111;
    }

    template<>
    inline bool CompareLess(const __v4si& LHS, const __v4si& RHS)
    {
        return _mm_movemask_epi8(_mm_cmplt_epi32(LHS, RHS)) == (int)0b00000000000000001111111111111111;
    }

    template<>
    inline bool CompareLess(const __v8hu& LHS, const __v8hu& RHS)
    {
        return _mm_movemask_epi8(_mm_cmplt_epi16(LHS, RHS)) == (int)0b00000000000000001111111111111111;
    }

    template<>
    inline bool CompareLess(const __v8hi& LHS, const __v8hi& RHS)
    {
        return _mm_movemask_epi8(_mm_cmplt_epi16(LHS, RHS)) == (int)0b00000000000000001111111111111111;
    }

    template<>
    inline bool CompareLess(const __v16qu& LHS, const __v16qu& RHS)
    {
        return _mm_movemask_epi8(_mm_cmplt_epi16(LHS, RHS)) == (int)0b00000000000000001111111111111111;
    }

    template<>
    inline bool CompareLess(const __v16qi& LHS, const __v16qi& RHS)
    {
        return _mm_movemask_epi8(_mm_cmplt_epi8(LHS, RHS)) == (int)0b00000000000000001111111111111111;
    }

#pragma mark CompareLessOrEqual

    template<typename RegisterType>
    bool CompareLessOrEqual(const RegisterType&, const RegisterType&);

#if __AVX__
    
    template<>
    inline bool CompareLessOrEqual(const __m128& LHS, const __m128& RHS)
    {
        return _mm_movemask_ps(_mm_cmp_ps(LHS, RHS, LessOrEqual)) == (int)0b00000000000000000000000000001111;
    }

    template<>
    inline bool CompareLessOrEqual(const __m128d& LHS, const __m128d& RHS)
    {
        return _mm_movemask_pd(_mm_cmp_pd(LHS, RHS, LessOrEqual)) == (int)0b00000000000000000000000000000011;
    }

    template<>
    inline bool CompareLessOrEqual(const __m256& LHS, const __m256& RHS)
    {
        return _mm256_movemask_ps(_mm256_cmp_ps(LHS, RHS, LessOrEqual)) == (int)0b00000000000000000000000011111111;
    }

    template<>
    inline bool CompareLessOrEqual(const __m256d& LHS, const __m256d& RHS)
    {
        return _mm256_movemask_pd(_mm256_cmp_pd(LHS, RHS, LessOrEqual)) == (int)0b00000000000000000000000000001111;
    }

#if __AVX2__
    
    template<>
    inline bool CompareLessOrEqual(const __v4du& LHS, const __v4du& RHS)
    {
        //swap the order of parameters so we see if RHS is greater than LHS
        return _mm256_movemask_epi8(_mm256_cmpgt_epi64(RHS, LHS)) == (int)0b11111111111111111111111111111111;
    }

    template<>
    inline bool CompareLessOrEqual(const __v4di& LHS, const __v4di& RHS)
    {
        //swap the order of parameters so we see if RHS is greater than LHS
        return _mm256_movemask_epi8(_mm256_cmpgt_epi64(RHS, LHS)) == (int)0b11111111111111111111111111111111;
    }

    template<>
    inline bool CompareLessOrEqual(const __v8su& LHS, const __v8su& RHS)
    {
        //swap the order of parameters so we see if RHS is greater than LHS
        return _mm256_movemask_epi8(_mm256_cmpgt_epi32(RHS, LHS)) == (int)0b11111111111111111111111111111111;
    }

    template<>
    inline bool CompareLessOrEqual(const __v8si& LHS, const __v8si& RHS)
    {
        //swap the order of parameters so we see if RHS is greater than LHS
        return _mm256_movemask_epi8(_mm256_cmpgt_epi32(RHS, LHS)) == (int)0b11111111111111111111111111111111;
    }

    template<>
    inline bool CompareLessOrEqual(const __v16hu& LHS, const __v16hu& RHS)
    {
        //swap the order of parameters so we see if RHS is greater than LHS
        return _mm256_movemask_epi8(_mm256_cmpgt_epi16(RHS, LHS)) == (int)0b11111111111111111111111111111111;
    }

    template<>
    inline bool CompareLessOrEqual(const __v16hi& LHS, const __v16hi& RHS)
    {
        //swap the order of parameters so we see if RHS is greater than LHS
        return _mm256_movemask_epi8(_mm256_cmpgt_epi16(RHS, LHS)) == (int)0b11111111111111111111111111111111;
    }

    template<>
    inline bool CompareLessOrEqual(const __v32qu& LHS, const __v32qu& RHS)
    {
        //swap the order of parameters so we see if RHS is greater than LHS
        return _mm256_movemask_epi8(_mm256_cmpgt_epi8(RHS, LHS)) == (int)0b11111111111111111111111111111111;
    }

    template<>
    inline bool CompareLessOrEqual(const __v32qi& LHS, const __v32qi& RHS)
    {
        //swap the order of parameters so we see if RHS is greater than LHS
        return _mm256_movemask_epi8(_mm256_cmpgt_epi8(LHS, RHS)) == (int)0b11111111111111111111111111111111;
    }

#endif //__AVX__
#endif //__AVX2__
    
    template<>
    inline bool CompareLessOrEqual(const __v2du& LHS, const __v2du& RHS)
    {
        //swap the order of parameters so we see if RHS is greater than LHS
        return _mm_movemask_epi8(_mm_cmpgt_epi64(RHS, Add(RHS, SetAllFromOne<__v2du>(1)))) == (int)0b00000000000000001111111111111111;
    }

    template<>
    inline bool CompareLessOrEqual(const __v2di& LHS, const __v2di& RHS)
    {
        //no cmple exists so add 1 to RHS
        return _mm_movemask_epi8(_mm_cmplt_epi32(LHS, Add(RHS, SetAllFromOne<__v2di>(1)))) == (int)0b00000000000000001111111111111111;
    }

    template<>
    inline bool CompareLessOrEqual(const __v4su& LHS, const __v4su& RHS)
    {
        //no cmple exists so add 1 to RHS
        return _mm_movemask_epi8(_mm_cmplt_epi32(LHS, Add(RHS, SetAllFromOne<__v4su>(1)))) == (int)0b00000000000000001111111111111111;
    }

    template<>
    inline bool CompareLessOrEqual(const __v4si& LHS, const __v4si& RHS)
    {
        //no cmple exists so add 1 to RHS
        return _mm_movemask_epi8(_mm_cmplt_epi32(LHS, Add(RHS, SetAllFromOne<__v4si>(1)))) == (int)0b00000000000000001111111111111111;
    }

    template<>
    inline bool CompareLessOrEqual(const __v8hu& LHS, const __v8hu& RHS)
    {
        //no cmple exists so add 1 to RHS
        return _mm_movemask_epi8(_mm_cmplt_epi16(LHS, Add(RHS, SetAllFromOne<__v8hu>(1)))) == (int)0b00000000000000001111111111111111;
    }

    template<>
    inline bool CompareLessOrEqual(const __v8hi& LHS, const __v8hi& RHS)
    {
        //no cmple exists so add 1 to RHS
        return _mm_movemask_epi8(_mm_cmplt_epi16(LHS, Add(RHS, SetAllFromOne<__v8hi>(1)))) == (int)0b00000000000000001111111111111111;
    }

    template<>
    inline bool CompareLessOrEqual(const __v16qu& LHS, const __v16qu& RHS)
    {
        //no cmple exists so add 1 to RHS
        return _mm_movemask_epi8(_mm_cmplt_epi16(LHS, Add(RHS, SetAllFromOne<__v16qu>(1)))) == (int)0b00000000000000001111111111111111;
    }

    template<>
    inline bool CompareLessOrEqual(const __v16qi& LHS, const __v16qi& RHS)
    {
        //no cmple exists so add 1 to RHS
        return _mm_movemask_epi8(_mm_cmplt_epi8(LHS, Add(RHS, SetAllFromOne<__v16qi>(1)))) == (int)0b00000000000000001111111111111111;
    }

#pragma mark GetGreater

    template<typename RegisterType>
    RegisterType GetGreater(const RegisterType&, const RegisterType&);

    template<>
    inline __m128 GetGreater(const __m128& LHS, const __m128& RHS)
    {
        return _mm_max_ps(LHS, RHS);
    }

    template<>
    inline __m128d GetGreater(const __m128d& LHS, const __m128d& RHS)
    {
        return _mm_max_pd(LHS, RHS);
    }

#if __AVX__
    
    template<>
    inline __m256 GetGreater(const __m256& LHS, const __m256& RHS)
    {
        return _mm256_max_ps(LHS, RHS);
    }

    template<>
    inline __m256d GetGreater(const __m256d& LHS, const __m256d& RHS)
    {
        return _mm256_max_pd(LHS, RHS);
    }

#if __AVX2__
    
    template<>
    inline __v4du GetGreater(const __v4du& LHS, const __v4du& RHS)
    {
        checkf(false, TEXT("Not supported"))
        return _mm256_max_epu32(LHS, RHS);
    }

    template<>
    inline __v4di GetGreater(const __v4di& LHS, const __v4di& RHS)
    {
        checkf(false, TEXT("Not supported"))
        return _mm256_max_epi32(LHS, RHS);
    }

    template<>
    inline __v8su GetGreater(const __v8su& LHS, const __v8su& RHS)
    {
        return _mm256_max_epu32(LHS, RHS);
    }

    template<>
    inline __v8si GetGreater(const __v8si& LHS, const __v8si& RHS)
    {
        return _mm256_max_epi32(LHS, RHS);
    }

    template<>
    inline __v16hu GetGreater(const __v16hu& LHS, const __v16hu& RHS)
    {
        return _mm256_max_epu16(LHS, RHS);
    }

    template<>
    inline __v16hi GetGreater(const __v16hi& LHS, const __v16hi& RHS)
    {
        return _mm256_max_epi16(LHS, RHS);
    }

    template<>
    inline  __v32qu GetGreater(const __v32qu& LHS, const __v32qu& RHS)
    {
        return _mm256_max_epu8(LHS, RHS);
    }

    template<>
    inline __v32qi GetGreater(const __v32qi& LHS, const __v32qi& RHS)
    {
        return _mm256_max_epu8(LHS, RHS);
    }

#endif //__AVX__
#endif //__AVX2_
    
    template<>
    inline __v2du GetGreater(const __v2du& LHS, const __v2du& RHS)
    {
        checkf(false, TEXT("Not supported"))
        return _mm_max_epu32(LHS, RHS);
    }

    template<>
    inline __v2di GetGreater(const __v2di& LHS, const __v2di& RHS)
    {
        checkf(false, TEXT("Not supported"))
        return _mm_max_epi32(LHS, RHS);;
    }

    template<>
    inline __v4su GetGreater(const __v4su& LHS, const __v4su& RHS)
    {
        return _mm_max_epu32(LHS, RHS);
    }

    template<>
    inline __v4si GetGreater(const __v4si& LHS, const __v4si& RHS)
    {
        return _mm_max_epi32(LHS, RHS);
    }

    template<>
    inline __v8hu GetGreater(const __v8hu& LHS, const __v8hu& RHS)
    {
        return _mm_max_epu16(LHS, RHS);
    }

    template<>
    inline __v8hi GetGreater(const __v8hi& LHS, const __v8hi& RHS)
    {
        return _mm_max_epi16(LHS, RHS);
    }

    template<>
    inline __v16qu GetGreater(const __v16qu& LHS, const __v16qu& RHS)
    {
        return _mm_max_epu8(LHS, RHS);
    }

    template<>
    inline __v16qi GetGreater(const __v16qi& LHS, const __v16qi& RHS)
    {
        return _mm_max_epi8(LHS, RHS);
    }

#pragma mark GetLesser

    template<typename RegisterType>
    RegisterType GetLesser(const RegisterType&, const RegisterType&);

    template<>
    inline __m128 GetLesser(const __m128& LHS, const __m128& RHS)
    {
        return _mm_min_ps(LHS, RHS);
    }

    template<>
    inline __m128d GetLesser(const __m128d& LHS, const __m128d& RHS)
    {
        return _mm_min_pd(LHS, RHS);
    }

#if __AVX__
    
    template<>
    inline __m256 GetLesser(const __m256& LHS, const __m256& RHS)
    {
        return _mm256_min_ps(LHS, RHS);
    }

    template<>
    inline __m256d GetLesser(const __m256d& LHS, const __m256d& RHS)
    {
        return _mm256_min_pd(LHS, RHS);
    }

#if __AVX2__
    
    template<>
    inline __v4du GetLesser(const __v4du& LHS, const __v4du& RHS)
    {
        checkf(false, TEXT("Not supported"))
        return _mm256_min_epu32(LHS, RHS);
    }

    template<>
    inline __v4di GetLesser(const __v4di& LHS, const __v4di& RHS)
    {
        checkf(false, TEXT("Not supported"))
        return _mm256_min_epi32(LHS, RHS);
    }

    template<>
    inline __v8su GetLesser(const __v8su& LHS, const __v8su& RHS)
    {
        return _mm256_min_epu32(LHS, RHS);
    }

    template<>
    inline __v8si GetLesser(const __v8si& LHS, const __v8si& RHS)
    {
        return _mm256_min_epi32(LHS, RHS);
    }

    template<>
    inline __v16hu GetLesser(const __v16hu& LHS, const __v16hu& RHS)
    {
        return _mm256_min_epu16(LHS, RHS);
    }

    template<>
    inline __v16hi GetLesser(const __v16hi& LHS, const __v16hi& RHS)
    {
        return _mm256_min_epi16(LHS, RHS);
    }

    template<>
    inline  __v32qu GetLesser(const __v32qu& LHS, const __v32qu& RHS)
    {
        return _mm256_min_epu8(LHS, RHS);
    }

    template<>
    inline __v32qi GetLesser(const __v32qi& LHS, const __v32qi& RHS)
    {
        return _mm256_min_epu8(LHS, RHS);
    }

#endif //__AVX__
#endif //__AVX2__
    
    template<>
    inline __v2du GetLesser(const __v2du& LHS, const __v2du& RHS)
    {
        checkf(false, TEXT("Not supported"))
        return _mm_min_epu32(LHS, RHS);
    }

    template<>
    inline __v2di GetLesser(const __v2di& LHS, const __v2di& RHS)
    {
        checkf(false, TEXT("Not supported"))
        return _mm_min_epi32(LHS, RHS);;
    }

    template<>
    inline __v4su GetLesser(const __v4su& LHS, const __v4su& RHS)
    {
        return _mm_min_epu32(LHS, RHS);
    }

    template<>
    inline __v4si GetLesser(const __v4si& LHS, const __v4si& RHS)
    {
        return _mm_min_epi32(LHS, RHS);
    }

    template<>
    inline __v8hu GetLesser(const __v8hu& LHS, const __v8hu& RHS)
    {
        return _mm_min_epu16(LHS, RHS);
    }

    template<>
    inline __v8hi GetLesser(const __v8hi& LHS, const __v8hi& RHS)
    {
        return _mm_min_epi16(LHS, RHS);
    }

    template<>
    inline __v16qu GetLesser(const __v16qu& LHS, const __v16qu& RHS)
    {
        return _mm_min_epu8(LHS, RHS);
    }

    template<>
    inline __v16qi GetLesser(const __v16qi& LHS, const __v16qi& RHS)
    {
        return _mm_min_epi8(LHS, RHS);
    }

#pragma mark FusedMultiplyAdd // A + B * C
    
    template<typename RegisterType>
    RegisterType FusedMultiplyAdd(const RegisterType&, const RegisterType&, const RegisterType&);

    template<>
    inline __m128 FusedMultiplyAdd(const __m128& A, const __m128& B, const __m128& C)
    {
        return _mm_fmadd_ps(A, B ,C);
    }

    template<>
    inline __m128d FusedMultiplyAdd(const __m128d& A, const __m128d& B, const __m128d& C)
    {
        return _mm_fmadd_pd(A, B ,C);
    }

#if __AVX__
    
    template<>
    inline __m256 FusedMultiplyAdd(const __m256& A, const __m256& B, const __m256& C)
    {
        return _mm256_fmadd_ps(A, B ,C);
    }

    template<>
    inline __m256d FusedMultiplyAdd(const __m256d& A, const __m256d& B, const __m256d& C)
    {
        return _mm256_fmadd_pd(A, B ,C);
    }

#if __AVX2__
    
    template<>
    inline __v4du FusedMultiplyAdd(const __v4du& A, const __v4du& B, const __v4du& C)
    {
        return static_cast<__v4du>(_mm256_fmadd_pd(static_cast<__m256d>(A), static_cast<__m256d>(B), static_cast<__m256d>(C)));
    }

    template<>
    inline __v4di FusedMultiplyAdd(const __v4di& A, const __v4di& B, const __v4di& C)
    {
        return static_cast<__v4di>(_mm256_fmadd_pd(static_cast<__m256d>(A), static_cast<__m256d>(B), static_cast<__m256d>(C)));
    }

    template<>
    inline __v8su FusedMultiplyAdd(const __v8su& A, const __v8su& B, const __v8su& C)
    {
        return static_cast<__v8su>(_mm256_fmadd_ps(static_cast<__m256>(A), static_cast<__m256>(B), static_cast<__m256>(C)));
    }

    template<>
    inline __v8si FusedMultiplyAdd(const __v8si& A, const __v8si& B, const __v8si& C)
    {
        return static_cast<__v8si>(_mm256_fmadd_ps(static_cast<__m256>(A), static_cast<__m256>(B), static_cast<__m256>(C)));
    }

    template<>
    inline __v16hu FusedMultiplyAdd(const __v16hu& A, const __v16hu& B, const __v16hu& C)
    {
        checkf(false, TEXT("Not supported")) //probably redesign this
        __m128 LowerA{_mm256_extractf128_ps(A, 0)};
        __m128 UpperA{_mm256_extractf128_ps(A, 1)};

        __m128 LowerB{_mm256_extractf128_ps(B, 0)};
        __m128 UpperB{_mm256_extractf128_ps(B, 1)};

        __m128 LowerC{_mm256_extractf128_ps(C, 0)};
        __m128 UpperC{_mm256_extractf128_ps(C, 1)};

        __m256 MadeToFloatA{_mm256_set_m128(UpperA, LowerA)};
        __m256 MadeToFloatB{_mm256_set_m128(UpperB, LowerB)};
        __m256 MadeToFloatC{_mm256_set_m128(UpperC, LowerC)};

        return static_cast<__v16hu>(_mm256_fmadd_ps(MadeToFloatA, MadeToFloatB, MadeToFloatC));
    }

    template<>
    inline __v16hi FusedMultiplyAdd(const __v16hi& A, const __v16hi& B, const __v16hi& C)
    {
        checkf(false, TEXT("Not supported")) //probably redesign this
        __m128 LowerA{_mm256_extractf128_ps(A, 0)};
        __m128 UpperA{_mm256_extractf128_ps(A, 1)};

        __m128 LowerB{_mm256_extractf128_ps(B, 0)};
        __m128 UpperB{_mm256_extractf128_ps(B, 1)};

        __m128 LowerC{_mm256_extractf128_ps(C, 0)};
        __m128 UpperC{_mm256_extractf128_ps(C, 1)};

        __m256 MadeToFloatA{_mm256_set_m128(UpperA, LowerA)};
        __m256 MadeToFloatB{_mm256_set_m128(UpperB, LowerB)};
        __m256 MadeToFloatC{_mm256_set_m128(UpperC, LowerC)};

        return static_cast<__v16hi>(_mm256_fmadd_ps(MadeToFloatA, MadeToFloatB, MadeToFloatC));
    }

    template<>
    inline  __v32qu FusedMultiplyAdd(const __v32qu& A, const __v32qu& B, const __v32qu& C)
    {
        checkf(false, TEXT("Not supported"))
        return __v32qu{};
    }

    template<>
    inline __v32qi FusedMultiplyAdd(const __v32qi& A, const __v32qi& B, const __v32qi& C)
    {
        checkf(false, TEXT("Not supported"))
        return __v32qi{};
    }

#endif //__AVX__
#endif //__AVX2__
    
    template<>
    inline __v2du FusedMultiplyAdd(const __v2du& A, const __v2du& B, const __v2du& C)
    {
        return static_cast<__v2du>(_mm_fmadd_pd(A, B, C));
    }

    template<>
    inline __v2di FusedMultiplyAdd(const __v2di& A, const __v2di& B, const __v2di& C)
    {
        return static_cast<__v2du>(_mm_fmadd_pd(A, B, C));
    }

    template<>
    inline __v4su FusedMultiplyAdd(const __v4su& A, const __v4su& B, const __v4su& C)
    {
        return static_cast<__v4su>(_mm_fmadd_ps(A, B, C));
    }

    template<>
    inline __v4si FusedMultiplyAdd(const __v4si& A, const __v4si& B, const __v4si& C)
    {
        return static_cast<__v4si>(_mm_fmadd_ps(A, B, C));
    }

    template<>
    inline __v8hu FusedMultiplyAdd(const __v8hu& A, const __v8hu& B, const __v8hu& C)
    {
        __m128 LowerA{(float32)A[0], (float32)A[1], (float32)A[2], (float32)A[3]};
        __m128 UpperA{(float32)A[4], (float32)A[5], (float32)A[6], (float32)A[7]};

        __m128 LowerB{(float32)B[0], (float32)B[1], (float32)B[2], (float32)B[3]};
        __m128 UpperB{(float32)B[4], (float32)B[5], (float32)B[6], (float32)B[7]};

        __m128 LowerC{(float32)C[0], (float32)C[1], (float32)C[2], (float32)C[3]};
        __m128 UpperC{(float32)C[4], (float32)C[5], (float32)C[6], (float32)C[7]};

        __m128 LowerResult{_mm_fmadd_ps(LowerA, LowerB, LowerC)};
        __m128 UpperResult{_mm_fmadd_ps(UpperA, UpperB, UpperC)};

        return __v8hu{(uint16)LowerResult[0], (uint16)LowerResult[1], (uint16)LowerResult[2], (uint16)LowerResult[3],
                      (uint16)UpperResult[0], (uint16)UpperResult[1], (uint16)UpperResult[2], (uint16)UpperResult[3]};
    }

    template<>
    inline __v8hi FusedMultiplyAdd(const __v8hi& A, const __v8hi& B, const __v8hi& C)
    {
        __m128 LowerA{(float32)A[0], (float32)A[1], (float32)A[2], (float32)A[3]};
        __m128 UpperA{(float32)A[4], (float32)A[5], (float32)A[6], (float32)A[7]};

        __m128 LowerB{(float32)B[0], (float32)B[1], (float32)B[2], (float32)B[3]};
        __m128 UpperB{(float32)B[4], (float32)B[5], (float32)B[6], (float32)B[7]};

        __m128 LowerC{(float32)C[0], (float32)C[1], (float32)C[2], (float32)C[3]};
        __m128 UpperC{(float32)C[4], (float32)C[5], (float32)C[6], (float32)C[7]};

        __m128 LowerResult{_mm_fmadd_ps(LowerA, LowerB, LowerC)};
        __m128 UpperResult{_mm_fmadd_ps(UpperA, UpperB, UpperC)};

        return __v8hi{(int16)LowerResult[0], (int16)LowerResult[1], (int16)LowerResult[2], (int16)LowerResult[3],
                      (int16)UpperResult[0], (int16)UpperResult[1], (int16)UpperResult[2], (int16)UpperResult[3]};
    }

    template<>
    inline __v16qu FusedMultiplyAdd(const __v16qu& A, const __v16qu& B, const __v16qu& C)
    {
        checkf(false, TEXT("Not supported"))
        return __v16qu{};
    }

    template<>
    inline __v16qi FusedMultiplyAdd(const __v16qi& A, const __v16qi& B, const __v16qi& C)
    {
        checkf(false, TEXT("Not supported"))
        return __v16qi{};
    }

#pragma mark BitwiseAnd

    template<typename RegisterType>
    RegisterType BitwiseAnd(const RegisterType&, const RegisterType&);

    template<>
    inline __m128 BitwiseAnd(const __m128& LHS, const __m128& RHS)
    {
        return _mm_and_ps(LHS, RHS);
    }

    template<>
    inline __m128d BitwiseAnd(const __m128d& LHS, const __m128d& RHS)
    {
        return _mm_and_pd(LHS, RHS);
    }

#if __AVX__
    
    template<>
    inline __m256 BitwiseAnd(const __m256& LHS, const __m256& RHS)
    {
        return _mm256_and_ps(LHS, RHS);
    }

    template<>
    inline __m256d BitwiseAnd(const __m256d& LHS, const __m256d& RHS)
    {
        return _mm256_and_pd(LHS, RHS);
    }

#if __AVX2__
    
    template<>
    inline __v4du BitwiseAnd(const __v4du& LHS, const __v4du& RHS)
    {
        return _mm256_and_si256(LHS, RHS);
    }

    template<>
    inline __v4di BitwiseAnd(const __v4di& LHS, const __v4di& RHS)
    {
        return _mm256_and_si256(LHS, RHS);
    }

    template<>
    inline __v8su BitwiseAnd(const __v8su& LHS, const __v8su& RHS)
    {
        return _mm256_and_si256(LHS, RHS);
    }

    template<>
    inline __v8si BitwiseAnd(const __v8si& LHS, const __v8si& RHS)
    {
        return _mm256_and_si256(LHS, RHS);
    }

    template<>
    inline __v16hu BitwiseAnd(const __v16hu& LHS, const __v16hu& RHS)
    {
        return _mm256_and_si256(LHS, RHS);
    }

    template<>
    inline __v16hi BitwiseAnd(const __v16hi& LHS, const __v16hi& RHS)
    {
        return _mm256_and_si256(LHS, RHS);
    }

    template<>
    inline  __v32qu BitwiseAnd(const __v32qu& LHS, const __v32qu& RHS)
    {
        return _mm256_and_si256(LHS, RHS);
    }

    template<>
    inline __v32qi BitwiseAnd(const __v32qi& LHS, const __v32qi& RHS)
    {
        return _mm256_and_si256(LHS, RHS);
    }

#endif //__AVX__
#endif //__AVX2__
    
    template<>
    inline __v2du BitwiseAnd(const __v2du& LHS, const __v2du& RHS)
    {
        return _mm_and_si128(LHS, RHS);
    }

    template<>
    inline __v2di BitwiseAnd(const __v2di& LHS, const __v2di& RHS)
    {
        return _mm_and_si128(LHS, RHS);
    }

    template<>
    inline __v4su BitwiseAnd(const __v4su& LHS, const __v4su& RHS)
    {
        return _mm_and_si128(LHS, RHS);
    }

    template<>
    inline __v4si BitwiseAnd(const __v4si& LHS, const __v4si& RHS)
    {
        return _mm_and_si128(LHS, RHS);
    }

    template<>
    inline __v8hu BitwiseAnd(const __v8hu& LHS, const __v8hu& RHS)
    {
        return _mm_and_si128(LHS, RHS);
    }

    template<>
    inline __v8hi BitwiseAnd(const __v8hi& LHS, const __v8hi& RHS)
    {
        return _mm_and_si128(LHS, RHS);
    }

    template<>
    inline __v16qu BitwiseAnd(const __v16qu& LHS, const __v16qu& RHS)
    {
        return _mm_and_si128(LHS, RHS);
    }

    template<>
    inline __v16qi BitwiseAnd(const __v16qi& LHS, const __v16qi& RHS)
    {
        return _mm_and_si128(LHS, RHS);
    }

#pragma mark BitwiseInclusiveOr

    template<typename RegisterType>
    RegisterType BitwiseInclusiveOr(const RegisterType&, const RegisterType&);

    template<>
    inline __m128 BitwiseInclusiveOr(const __m128& LHS, const __m128& RHS)
    {
        return _mm_or_ps(LHS, RHS);
    }

    template<>
    inline __m128d BitwiseInclusiveOr(const __m128d& LHS, const __m128d& RHS)
    {
        return _mm_or_pd(LHS, RHS);
    }

#if __AVX__
    
    template<>
    inline __m256 BitwiseInclusiveOr(const __m256& LHS, const __m256& RHS)
    {
        return _mm256_or_ps(LHS, RHS);
    }

    template<>
    inline __m256d BitwiseInclusiveOr(const __m256d& LHS, const __m256d& RHS)
    {
        return _mm256_or_pd(LHS, RHS);
    }

#if __AVX2__
    
    template<>
    inline __v4du BitwiseInclusiveOr(const __v4du& LHS, const __v4du& RHS)
    {
        return _mm256_or_si256(LHS, RHS);
    }

    template<>
    inline __v4di BitwiseInclusiveOr(const __v4di& LHS, const __v4di& RHS)
    {
        return _mm256_or_si256(LHS, RHS);
    }

    template<>
    inline __v8su BitwiseInclusiveOr(const __v8su& LHS, const __v8su& RHS)
    {
        return _mm256_or_si256(LHS, RHS);
    }

    template<>
    inline __v8si BitwiseInclusiveOr(const __v8si& LHS, const __v8si& RHS)
    {
        return _mm256_or_si256(LHS, RHS);
    }

    template<>
    inline __v16hu BitwiseInclusiveOr(const __v16hu& LHS, const __v16hu& RHS)
    {
        return _mm256_or_si256(LHS, RHS);
    }

    template<>
    inline __v16hi BitwiseInclusiveOr(const __v16hi& LHS, const __v16hi& RHS)
    {
        return _mm256_or_si256(LHS, RHS);
    }

    template<>
    inline  __v32qu BitwiseInclusiveOr(const __v32qu& LHS, const __v32qu& RHS)
    {
        return _mm256_or_si256(LHS, RHS);
    }

    template<>
    inline __v32qi BitwiseInclusiveOr(const __v32qi& LHS, const __v32qi& RHS)
    {
        return _mm256_or_si256(LHS, RHS);
    }

#endif //__AVX__
#endif //__AVX2__
    
    template<>
    inline __v2du BitwiseInclusiveOr(const __v2du& LHS, const __v2du& RHS)
    {
        return _mm_or_si128(LHS, RHS);
    }

    template<>
    inline __v2di BitwiseInclusiveOr(const __v2di& LHS, const __v2di& RHS)
    {
        return _mm_or_si128(LHS, RHS);
    }

    template<>
    inline __v4su BitwiseInclusiveOr(const __v4su& LHS, const __v4su& RHS)
    {
        return _mm_or_si128(LHS, RHS);
    }

    template<>
    inline __v4si BitwiseInclusiveOr(const __v4si& LHS, const __v4si& RHS)
    {
        return _mm_or_si128(LHS, RHS);
    }

    template<>
    inline __v8hu BitwiseInclusiveOr(const __v8hu& LHS, const __v8hu& RHS)
    {
        return _mm_or_si128(LHS, RHS);
    }

    template<>
    inline __v8hi BitwiseInclusiveOr(const __v8hi& LHS, const __v8hi& RHS)
    {
        return _mm_or_si128(LHS, RHS);
    }

    template<>
    inline __v16qu BitwiseInclusiveOr(const __v16qu& LHS, const __v16qu& RHS)
    {
        return _mm_or_si128(LHS, RHS);
    }

    template<>
    inline __v16qi BitwiseInclusiveOr(const __v16qi& LHS, const __v16qi& RHS)
    {
        return _mm_or_si128(LHS, RHS);
    }

#pragma mark BitwiseExclusiveOr

    template<typename RegisterType>
    RegisterType BitwiseExclusiveOr(const RegisterType&, const RegisterType&);

    template<>
    inline __m128 BitwiseExclusiveOr(const __m128& LHS, const __m128& RHS)
    {
        return _mm_xor_ps(LHS, RHS);
    }

    template<>
    inline __m128d BitwiseExclusiveOr(const __m128d& LHS, const __m128d& RHS)
    {
        return _mm_xor_pd(LHS, RHS);
    }

#if __AVX__
    
    template<>
    inline __m256 BitwiseExclusiveOr(const __m256& LHS, const __m256& RHS)
    {
        return _mm256_xor_ps(LHS, RHS);
    }

    template<>
    inline __m256d BitwiseExclusiveOr(const __m256d& LHS, const __m256d& RHS)
    {
        return _mm256_xor_pd(LHS, RHS);
    }

#if __AVX2__
    template<>
    inline __v4du BitwiseExclusiveOr(const __v4du& LHS, const __v4du& RHS)
    {
        return _mm256_xor_si256(LHS, RHS);
    }

    template<>
    inline __v4di BitwiseExclusiveOr(const __v4di& LHS, const __v4di& RHS)
    {
        return _mm256_xor_si256(LHS, RHS);
    }

    template<>
    inline __v8su BitwiseExclusiveOr(const __v8su& LHS, const __v8su& RHS)
    {
        return _mm256_xor_si256(LHS, RHS);
    }

    template<>
    inline __v8si BitwiseExclusiveOr(const __v8si& LHS, const __v8si& RHS)
    {
        return _mm256_xor_si256(LHS, RHS);
    }

    template<>
    inline __v16hu BitwiseExclusiveOr(const __v16hu& LHS, const __v16hu& RHS)
    {
        return _mm256_xor_si256(LHS, RHS);
    }

    template<>
    inline __v16hi BitwiseExclusiveOr(const __v16hi& LHS, const __v16hi& RHS)
    {
        return _mm256_xor_si256(LHS, RHS);
    }

    template<>
    inline  __v32qu BitwiseExclusiveOr(const __v32qu& LHS, const __v32qu& RHS)
    {
        return _mm256_xor_si256(LHS, RHS);
    }

    template<>
    inline __v32qi BitwiseExclusiveOr(const __v32qi& LHS, const __v32qi& RHS)
    {
        return _mm256_xor_si256(LHS, RHS);
    }

#endif //__AVX__
#endif //__AVX2__
    
    template<>
    inline __v2du BitwiseExclusiveOr(const __v2du& LHS, const __v2du& RHS)
    {
        return _mm_xor_si128(LHS, RHS);
    }

    template<>
    inline __v2di BitwiseExclusiveOr(const __v2di& LHS, const __v2di& RHS)
    {
        return _mm_xor_si128(LHS, RHS);
    }

    template<>
    inline __v4su BitwiseExclusiveOr(const __v4su& LHS, const __v4su& RHS)
    {
        return _mm_xor_si128(LHS, RHS);
    }

    template<>
    inline __v4si BitwiseExclusiveOr(const __v4si& LHS, const __v4si& RHS)
    {
        return _mm_xor_si128(LHS, RHS);
    }

    template<>
    inline __v8hu BitwiseExclusiveOr(const __v8hu& LHS, const __v8hu& RHS)
    {
        return _mm_xor_si128(LHS, RHS);
    }

    template<>
    inline __v8hi BitwiseExclusiveOr(const __v8hi& LHS, const __v8hi& RHS)
    {
        return _mm_xor_si128(LHS, RHS);
    }

    template<>
    inline __v16qu BitwiseExclusiveOr(const __v16qu& LHS, const __v16qu& RHS)
    {
        return _mm_xor_si128(LHS, RHS);
    }

    template<>
    inline __v16qi BitwiseExclusiveOr(const __v16qi& LHS, const __v16qi& RHS)
    {
        return _mm_xor_si128(LHS, RHS);
    }

    namespace Private
    {

        template<typename RegisterType>
        class alignas(RegisterType) TVectorRegister final
        {
            using ElementType = ElementType<RegisterType>;

#define Set1(value) SetAllFromOne<RegisterType>(value)

        public:

            NODISCARD constexpr static auto GetNumElements()
            {
                return sizeof(RegisterType) / sizeof(ElementType);
            }

            constexpr INLINE explicit TVectorRegister(ElementType Value = static_cast<ElementType>(0))
                    : Register(Set1(Value))
            {
            }

            template<typename... Elements>
            constexpr INLINE explicit TVectorRegister(Elements... ElementValues)
                    : Register{static_cast<ElementType>(ElementValues)...}
            {
                static_assert(sizeof...(ElementValues) == GetNumElements());
            }

            INLINE TVectorRegister(const TVectorRegister& Other)
                    : Register(Other.Register)
            {
            }

            INLINE TVectorRegister(TVectorRegister&& Other) noexcept
                    : Register(MoveTemp(Other.Register))
            {
            }

            INLINE explicit TVectorRegister(RegisterType Other)
                    : Register(Other)
            {
            }

            INLINE RegisterType& Get()
            {
                return Register;
            }

#pragma mark Operators

            template<typename... Elements>
            INLINE TVectorRegister& operator=(Elements... ElementValues)
            {
                Register = {ElementValues...};
                return *this;
            }

            INLINE TVectorRegister& operator=(ElementType Value)
            {
                Register = Set1(Value);
                return *this;
            }

            INLINE TVectorRegister& operator=(const TVectorRegister& Other)
            {
                Register = Other.Register;
                return *this;
            }

            INLINE TVectorRegister& operator=(TVectorRegister&& Other) noexcept
            {
                Register = MoveTemp(Other.Register);
                return *this;
            }

            INLINE TVectorRegister& operator=(RegisterType Other)
            {
                Register = MoveTemp(Other);
                return *this;
            }

            INLINE RegisterType& operator*()
            {
                return Register;
            }

            // returns a COPY of the element at index
            INLINE ElementType operator[](const size_t Index) const
            {
                check(Index < GetNumElements())
                return Register[Index];
            }

            INLINE TVectorRegister operator/(ElementType Other) const
            {
                return TVectorRegister{Divide(Register, Set1(Other))};
            }

            INLINE TVectorRegister operator/(const RegisterType &Other) const
            {
                return TVectorRegister{Divide(Register, Other)};
            }

            INLINE TVectorRegister operator/(const TVectorRegister &Other) const
            {
                return TVectorRegister{Divide(Register, Other.Register)};
            }

            INLINE TVectorRegister &operator/=(ElementType Other)
            {
                Register = Divide(Register, Set1(Other));
                return *this;
            }

            INLINE TVectorRegister &operator/=(const RegisterType &Other)
            {
                Register = Divide(Register, Other);
                return *this;
            }

            INLINE TVectorRegister &operator/=(const TVectorRegister &Other)
            {
                Register = Divide(Register, Other.Register);
                return *this;
            }

            INLINE TVectorRegister operator+(ElementType Other) const
            {
                return TVectorRegister{Add(Register, Set1(Other))};
            }

            INLINE TVectorRegister operator+(const RegisterType &Other) const
            {
                return Add(Register, Other);
            }

            INLINE TVectorRegister operator+(const TVectorRegister &Other) const
            {
                return TVectorRegister{Add(Register, Other.Register)};
            }

            INLINE TVectorRegister &operator+=(ElementType Other)
            {
                Register = Add(Register, Set1(Other));
                return *this;
            }

            INLINE TVectorRegister &operator+=(const RegisterType &Other)
            {
                Register = Add(Register, Other);
                return *this;
            }

            INLINE TVectorRegister &operator+=(const TVectorRegister &Other)
            {
                Register = Add(Register, Other.Register);
                return *this;
            }

            INLINE TVectorRegister operator-(ElementType Other) const
            {
                return TVectorRegister{Subtract(Register, Set1(Other))};
            }

            INLINE TVectorRegister operator-(const RegisterType &Other) const
            {
                return TVectorRegister{Subtract(Register, Other)};
            }

            INLINE TVectorRegister operator-(const TVectorRegister &Other) const
            {
                return TVectorRegister{Subtract(Register, Other.Register)};
            }

            INLINE TVectorRegister &operator-=(ElementType Other)
            {
                Register = Subtract(Register, Set1(Other));
                return *this;
            }

            INLINE TVectorRegister &operator-=(const RegisterType &Other)
            {
                Register = Subtract(Register, Other);
                return *this;
            }

            INLINE TVectorRegister &operator-=(const TVectorRegister &Other)
            {
                Register = Subtract(Register, Other.Register);
                return *this;
            }

            INLINE TVectorRegister operator*(ElementType Other) const
            {
                return TVectorRegister{Multiply(Register, Set1(Other))};
            }

            INLINE TVectorRegister operator*(const RegisterType &Other) const
            {
                return TVectorRegister{Multiply(Register, Other)};
            }

            INLINE TVectorRegister operator*(const TVectorRegister &Other) const
            {
                return TVectorRegister{Multiply(Register, Other.Register)};
            }

            INLINE TVectorRegister &operator*=(ElementType Other)
            {
                Register = Multiply(Register, Set1(Other));
                return *this;
            }

            INLINE TVectorRegister &operator*=(const RegisterType &Other)
            {
                Register = Multiply(Register, Other);
                return *this;
            }

            INLINE TVectorRegister &operator*=(const TVectorRegister &Other)
            {
                Register = Multiply(Register, Other.Register);
                return *this;
            }

            INLINE bool operator==(const RegisterType &Other) const
            {
                return CompareEqual(Register, Other);
            }

            INLINE bool operator==(const TVectorRegister &Other) const
            {
                return CompareEqual(Register, Other.Register);
            }

            INLINE bool operator==(ElementType Other) const
            {
                return CompareEqual(Register, Set1(Other));
            }

            INLINE bool operator!=(ElementType Other) const
            {
                return !CompareEqual(Register, Set1(Other));
            }

            INLINE bool operator!=(const RegisterType& Other) const
            {
                return !CompareEqual(Register, Other);
            }

            INLINE bool operator!=(const TVectorRegister &Other) const
            {
                return !CompareEqual(Register, Other.Register);
            }

            INLINE bool operator>=(const RegisterType &Other) const
            {
                return CompareGreaterOrEqual(Register, Other);
            }

            INLINE bool operator>=(const TVectorRegister &Other) const
            {
                return CompareGreaterOrEqual(Register, Other.Register);
            }

            INLINE bool operator>=(ElementType Other) const
            {
                return CompareGreaterOrEqual(Register, Set1(Other));
            }

            INLINE bool operator>(const RegisterType &Other) const
            {
                return CompareGreater(Register, Other);
            }

            INLINE bool operator>(const TVectorRegister &Other) const
            {
                return CompareGreater(Register, Other.Register);
            }

            INLINE bool operator>(ElementType Other) const
            {
                return CompareGreater(Register, Set1(Other));
            }

            INLINE bool operator<=(const RegisterType &Other) const
            {
                return CompareLessOrEqual(Register, Other);
            }

            INLINE bool operator<=(const TVectorRegister &Other) const
            {
                return CompareLessOrEqual(Register, Other.Register);
            }

            INLINE bool operator<=(ElementType Other) const
            {
                return CompareLessOrEqual(Register, Set1(Other));
            }

            INLINE bool operator<(const RegisterType &Other) const
            {
                return CompareLess(Register, Other);
            }

            INLINE bool operator<(const TVectorRegister &Other) const
            {
                return CompareLess(Register, Other.Register);
            }

            INLINE bool operator<(ElementType Other) const
            {
                return CompareLess(Register, Set1(Other));
            }

            INLINE TVectorRegister operator&(const RegisterType& Other) const
            {
                return TVectorRegister{BitwiseAnd(Register, Other)};
            }

            INLINE TVectorRegister operator&(const TVectorRegister& Other) const
            {
                return TVectorRegister{BitwiseAnd(Register, Other.Register)};
            }

            INLINE TVectorRegister operator&(ElementType Other) const
            {
                return TVectorRegister{BitwiseAnd(Register, Set1(Other))};
            }

            INLINE TVectorRegister& operator&=(const RegisterType& Other)
            {
                Register = BitwiseAnd(Register, Other);
                return *this;
            }

            INLINE TVectorRegister& operator&=(const TVectorRegister& Other)
            {
                Register = BitwiseAnd(Register, Other.Register);
                return *this;
            }

            INLINE TVectorRegister& operator&=(ElementType Other)
            {
                Register = BitwiseAnd(Register, Set1(Other));
                return *this;
            }

            //returns a register with all the smallest elements
            INLINE TVectorRegister operator|(const RegisterType& Other) const
            {
                return TVectorRegister{GetLesser(Register, Other)};
            }

            //returns a register with all the smallest elements
            INLINE TVectorRegister operator|(const TVectorRegister& Other) const
            {
                return TVectorRegister{GetLesser(Register, Other.Register)};
            }

            //returns a register with all the smallest elements
            INLINE TVectorRegister operator|(ElementType Other) const
            {
                return TVectorRegister{GetLesser(Register, Set1(Other))};
            }

            //returns a register with all the smallest elements
            INLINE TVectorRegister& operator|=(const RegisterType& Other)
            {
                Register = GetLesser(Register, Other);
                return *this;
            }

            //returns a register with all the smallest elements
            INLINE TVectorRegister& operator|=(const TVectorRegister& Other)
            {
                Register = GetLesser(Register, Other.Register);
                return *this;
            }

            //returns a register with all the smallest elements
            INLINE TVectorRegister& operator|=(ElementType Other)
            {
                Register = GetLesser(Register, Set1(Other));
                return *this;
            }

            //returns a register with all the largest elements
            INLINE TVectorRegister operator^(const RegisterType& Other) const
            {
                return TVectorRegister{GetGreater(Register, Other)};
            }

            //returns a register with all the largest elements
            INLINE TVectorRegister operator^(const TVectorRegister& Other) const
            {
                return TVectorRegister{GetGreater(Register, Other.Register)};
            }

            //returns a register with all the largest elements
            INLINE TVectorRegister operator^(ElementType Other) const
            {
                return TVectorRegister{GetGreater(Register, Set1(Other))};
            }

            //returns a register with all the largest elements
            INLINE TVectorRegister& operator^=(const RegisterType& Other)
            {
                Register = GetGreater(Register, Other);
                return *this;
            }

            //returns a register with all the largest elements
            INLINE TVectorRegister& operator^=(const TVectorRegister& Other)
            {
                Register = GetGreater(Register, Other.Register);
                return *this;
            }

            //returns a register with all the largest elements
            INLINE TVectorRegister& operator^=(ElementType Other)
            {
                Register = GetGreater(Register, Set1(Other));
                return *this;
            }

            INLINE TVectorRegister& operator~()
            {
                Register = BitwiseExclusiveOr(Register, Set1(std::numeric_limits<ElementType>::max()));
                return *this;
            }

            INLINE TVectorRegister& operator++()
            {
                Register = Add(Register, Set1(1));
                return *this;
            }

            INLINE TVectorRegister& operator--()
            {
                Register = Subtract(Register, Set1(1));
                return *this;
            }

            RegisterType Register;

#undef Set1
            
        };

    }

#pragma mark Typedefs

    using float32_4 = Private::TVectorRegister<__m128>;
    using float64_2 = Private::TVectorRegister<__m128d>;

    using uint64_2 = Private::TVectorRegister<__v2du>;
    using int64_2 = Private::TVectorRegister<__v2di>;
    using uint32_4 = Private::TVectorRegister<__v4su>;
    using int32_4 = Private::TVectorRegister<__v4si>;
    using uint16_8 = Private::TVectorRegister<__v8hu>;
    using int16_8 = Private::TVectorRegister<__v8hi>;
    using uint8_16 = Private::TVectorRegister<__v16qu>;
    using int8_16 = Private::TVectorRegister<__v16qi>;

#if __AVX__
    
    using float32_8 = Private::TVectorRegister<__m256>;
    using float64_4 = Private::TVectorRegister<__m256d>;

    using uint64_4 = Private::TVectorRegister<__v4du>;
    using int64_4  = Private::TVectorRegister<__v4di>;
    using uint32_8 = Private::TVectorRegister<__v8su>;
    using int32_8 = Private::TVectorRegister<__v8si>;
    using uint16_16 = Private::TVectorRegister<__v16hu>;
    using int16_16 = Private::TVectorRegister<__v16hi>;
    using uint8_32 = Private::TVectorRegister<__v32qu>;
    using int8_32 = Private::TVectorRegister<__v32qi>;

#endif //__AVX__
    
}

#endif //SIMD_ENABLE
