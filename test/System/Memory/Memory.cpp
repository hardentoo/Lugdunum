#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <lug/System/Memory.hpp>
#include <System/Memory/Utils.hpp>

TEST(Memory, RawPointerOne) {
    #define TEST_RAW_POINTER_ONE(alignment)                                                         \
        {                                                                                           \
            const char* file = "Test";                                                              \
            const size_t line = 42;                                                                 \
                                                                                                    \
            MockArena arena;                                                                        \
            char buffer[4096];                                                                      \
                                                                                                    \
            EXPECT_CALL(arena, allocate(_, alignment, _, file, line))                               \
                .Times(2)                                                                           \
                .WillRepeatedly(Return(&(buffer)));                                                 \
                                                                                                    \
            EXPECT_CALL(arena, free(&(buffer)))                                                     \
                .Times(2);                                                                          \
                                                                                                    \
            {                                                                                       \
                int* ptr = lug::System::Memory::new_one<int>(alignment, file, line, arena);         \
                lug::System::Memory::delete_one(ptr, arena);                                        \
            }                                                                                       \
                                                                                                    \
            {                                                                                       \
                int* ptr = lug::System::Memory::new_one<int>(alignment, file, line, arena, 42);     \
                ASSERT_EQ(*ptr, 42);                                                                \
                lug::System::Memory::delete_one(ptr, arena);                                        \
            }                                                                                       \
                                                                                                    \
        }

    #define TEST_RAW_POINTER_ONE_NULL(alignment)                                                    \
        {                                                                                           \
            const char* file = "Test";                                                              \
            const size_t line = 42;                                                                 \
                                                                                                    \
            NullArena arena;                                                                        \
                                                                                                    \
            {                                                                                       \
                int* ptr = lug::System::Memory::new_one<int>(alignment, file, line, arena);         \
                ASSERT_EQ(ptr, nullptr);                                                            \
                lug::System::Memory::delete_one(ptr, arena);                                        \
            }                                                                                       \
                                                                                                    \
            {                                                                                       \
                int* ptr = lug::System::Memory::new_one<int>(alignment, file, line, arena, 42);     \
                ASSERT_EQ(ptr, nullptr);                                                            \
                lug::System::Memory::delete_one(ptr, arena);                                        \
            }                                                                                       \
                                                                                                    \
        }

    #define TEST_RAW_POINTER_ONE_DTR(alignment)                                                         \
        {                                                                                               \
            const char* file = "Test";                                                                  \
            const size_t line = 42;                                                                     \
                                                                                                        \
            MockArena arena;                                                                            \
            char buffer[4096];                                                                          \
                                                                                                        \
            EXPECT_CALL(arena, allocate(_, alignment, _, file, line))                                   \
                .Times(1)                                                                               \
                .WillRepeatedly(Return(&(buffer)));                                                     \
                                                                                                        \
            EXPECT_CALL(arena, free(&(buffer)))                                                         \
                .Times(1);                                                                              \
                                                                                                        \
            MockObject* ptr = lug::System::Memory::new_one<MockObject>(alignment, file, line, arena);   \
                                                                                                        \
            EXPECT_CALL(*ptr, destructor())                                                             \
                .Times(1);                                                                              \
                                                                                                        \
            lug::System::Memory::delete_one(ptr, arena);                                                \
        }

    TEST_MULTIPLE_ALIGNMENTS(TEST_RAW_POINTER_ONE);
    TEST_MULTIPLE_ALIGNMENTS(TEST_RAW_POINTER_ONE_NULL);
    TEST_MULTIPLE_ALIGNMENTS(TEST_RAW_POINTER_ONE_DTR);
}

