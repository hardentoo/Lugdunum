#include <gtest/gtest.h>
#include <lug/Math/Matrix.hpp>
#include <lug/Math/Vector.hpp>

// TODO: Really test all operators and values
// TODO: Test the determinant
// TODO: Test the transpose

namespace lug {
namespace Math {

TEST(Matrix2x2, Constructors) {
    Mat2x2i matrix{ 1, 2, 3, 4 };

    ASSERT_EQ(matrix(0, 0), 1);
    ASSERT_EQ(matrix(0, 1), 2);
    ASSERT_EQ(matrix(1, 0), 3);
    ASSERT_EQ(matrix(1, 1), 4);
}

TEST(Matrix2x2, GeneralOperators) {
    Mat2x2f matrixL(1.0f);
    Mat2x2f matrixM(1.0f);

    Vec2f vectorU(1.0f);
    Vec2f vectorV(1.0f);

    float x = 1.0f;

    Vec2f vectorA = matrixM * vectorU;
    Vec2f vectorB = vectorV * matrixM;

    (void)(vectorA);
    (void)(vectorB);

    Mat2x2f matrixN = x / matrixM;
    Mat2x2f matrixO = matrixM / x;
    Mat2x2f matrixP = x * matrixM;
    Mat2x2f matrixQ = matrixM * x;

    (void)(matrixN);
    (void)(matrixO);
    (void)(matrixP);

    EXPECT_TRUE(!(matrixM != matrixQ));
    EXPECT_TRUE(matrixM == matrixL);
}

TEST(Matrix2x2, InverseOperators) {
    const Mat2x2f goodIdentity = Mat2x2f::identity();

    {
        const Mat2x2f matrix{ 1, 2, 3, 4 };
        const Mat2x2f inverse = matrix.inverse();
        const Mat2x2f identity = matrix * inverse;

        for (uint8_t row = 0; row < matrix.getRows(); ++row) {
            for (uint8_t col = 0; col < matrix.getColumns(); ++col) {
                ASSERT_NEAR(identity(row, col), goodIdentity(row, col), 0.01f)
                    << "row = " << static_cast<int>(row) << "\n"
                    << "col = " << static_cast<int>(col);
            }
        }
    }

    {
        const Mat2x2f matrix{ 1, 2, 3, 4 };
        const Mat2x2f identity = matrix / matrix;

        for (uint8_t row = 0; row < matrix.getRows(); ++row) {
            for (uint8_t col = 0; col < matrix.getColumns(); ++col) {
                ASSERT_NEAR(identity(row, col), goodIdentity(row, col), 0.01f)
                    << "row = " << static_cast<int>(row) << "\n"
                    << "col = " << static_cast<int>(col);
            }
        }
    }
}

TEST(Matrix2x2, Size) {
    ASSERT_EQ(Mat2x2f().getRows(), 2);
    ASSERT_EQ(Mat2x2f().getColumns(), 2);

    ASSERT_EQ(sizeof(Mat2x2f), 4 * sizeof(float));
}

TEST(Matrix2x2, Addition) {
    Mat2x2f matrixA{
        2.f, -6.f,
        7.f,  8.f
    };
    Mat2x2f matrixB{
         1.f, 5.f,
        -7.f, 3.f
    };

    // Operator Tests
    {
        const Mat2x2f result = matrixA + matrixB;

        const Mat2x2f correctResult{
            3.f, -1.f,
            0.f,  11.f
        };

        for (uint8_t row = 0; row < result.getRows(); ++row) {
            for (uint8_t col = 0; col < result.getColumns(); ++col) {
                ASSERT_NEAR(result(row, col), correctResult(row, col), 0.01f)
                    << "row = " << static_cast<int>(row) << "\n"
                    << "col = " << static_cast<int>(col);
            }
        }

        matrixA += matrixB;

        for (uint8_t row = 0; row < matrixA.getRows(); ++row) {
            for (uint8_t col = 0; col < matrixA.getColumns(); ++col) {
                ASSERT_NEAR(matrixA(row, col), correctResult(row, col), 0.01f)
                    << "row = " << static_cast<int>(row) << "\n"
                    << "col = " << static_cast<int>(col);
            }
        }
    }

    // Scalar test
    {
        const Mat2x2f result = matrixB + 1.0f;

        const Mat2x2f correctResult{
            1.f + 1.0f,  5.f + 1.0f,
            -7.f + 1.0f,  3.f + 1.0f
        };

        for (uint8_t row = 0; row < result.getRows(); ++row) {
            for (uint8_t col = 0; col < result.getColumns(); ++col) {
                ASSERT_NEAR(result(row, col), correctResult(row, col), 0.01f)
                    << "row = " << static_cast<int>(row) << "\n"
                    << "col = " << static_cast<int>(col);
            }
        }

    };

}

TEST(Matrix2x2, Substraction) {
    Mat2x2f matrixA{
        2.f, -6.f,
        7.f,  8.f
    };
    Mat2x2f matrixB{
         1.f, 5.f,
        -7.f, 3.f
    };

    // Operator Tests
    {
        const Mat2x2f result = matrixA - matrixB;

        const Mat2x2f correctResult{
            1.f, -11.f,
            14.f, 5.f
        };

        for (uint8_t row = 0; row < result.getRows(); ++row) {
            for (uint8_t col = 0; col < result.getColumns(); ++col) {
                ASSERT_NEAR(result(row, col), correctResult(row, col), 0.01f)
                    << "row = " << static_cast<int>(row) << "\n"
                    << "col = " << static_cast<int>(col);
            }
        }

        matrixA -= matrixB;

        for (uint8_t row = 0; row < matrixA.getRows(); ++row) {
            for (uint8_t col = 0; col < matrixA.getColumns(); ++col) {
                ASSERT_NEAR(matrixA(row, col), correctResult(row, col), 0.01f)
                    << "row = " << static_cast<int>(row) << "\n"
                    << "col = " << static_cast<int>(col);
            }
        }
    }

    // Scalar Tests
    {
        const Mat2x2f result = matrixB - 1.f;

        const Mat2x2f correctResult{
            1.f - 1.f,  5.f - 1.f,
            -7.f - 1.f,  3.f - 1.f
        };

        for (uint8_t row = 0; row < result.getRows(); ++row) {
            for (uint8_t col = 0; col < result.getColumns(); ++col) {
                ASSERT_NEAR(result(row, col), correctResult(row, col), 0.01f)
                    << "row = " << static_cast<int>(row) << "\n"
                    << "col = " << static_cast<int>(col);
            }
        }
    }
}

TEST(Matrix2x2, Multiplication) {
    Mat2x2f matrixA{
        2.f, -6.f,
        7.f,  8.f
    };
    Mat2x2f matrixB{
         1.f, 5.f,
        -7.f, 3.f
    };

    // Operator Tests
    {
        const Mat2x2f result = matrixA * matrixB;

        const Mat2x2f correctResult{
            44.f, -8.f,
            -49.f,  59.f
        };

        for (uint8_t row = 0; row < result.getRows(); ++row) {
            for (uint8_t col = 0; col < result.getColumns(); ++col) {
                ASSERT_NEAR(result(row, col), correctResult(row, col), 0.01f)
                    << "row = " << static_cast<int>(row) << "\n"
                    << "col = " << static_cast<int>(col);
            }
        }

        matrixA *= matrixB;

        for (uint8_t row = 0; row < matrixA.getRows(); ++row) {
            for (uint8_t col = 0; col < matrixA.getColumns(); ++col) {
                ASSERT_NEAR(matrixA(row, col), correctResult(row, col), 0.01f)
                    << "row = " << static_cast<int>(row) << "\n"
                    << "col = " << static_cast<int>(col);
            }
        }
    }

    // Scalar Test
    {
        const Mat2x2f result = matrixB * 2.f;

        const Mat2x2f correctResult{
            1.f * 2.f,  5.f * 2.f,
            -7.f * 2.f,  3.f * 2.f
        };

        for (uint8_t row = 0; row < result.getRows(); ++row) {
            for (uint8_t col = 0; col < result.getColumns(); ++col) {
                ASSERT_NEAR(result(row, col), correctResult(row, col), 0.01f)
                    << "row = " << static_cast<int>(row) << "\n"
                    << "col = " << static_cast<int>(col);
            }
        }
    }
}

TEST(Matrix2x2, Division) {
    Mat2x2f matrixA{
        2.f, -6.f,
        7.f,  8.f
    };
    Mat2x2f matrixB{
         1.f, 5.f,
        -7.f, 3.f
    };

    // Operator Tests
    {
        const Mat2x2f result = matrixA / matrixB;

        const Mat2x2f correctResult{
            -18.f / 19.f, -8.f / 19.f,
            77.f / 38.f, -27.f / 38.f
        };

        for (uint8_t row = 0; row < result.getRows(); ++row) {
            for (uint8_t col = 0; col < result.getColumns(); ++col) {
                ASSERT_NEAR(result(row, col), correctResult(row, col), 0.01f)
                    << "row = " << static_cast<int>(row) << "\n"
                    << "col = " << static_cast<int>(col);
            }
        }

        matrixA /= matrixB;

        for (uint8_t row = 0; row < matrixA.getRows(); ++row) {
            for (uint8_t col = 0; col < matrixA.getColumns(); ++col) {
                ASSERT_NEAR(matrixA(row, col), correctResult(row, col), 0.01f)
                    << "row = " << static_cast<int>(row) << "\n"
                    << "col = " << static_cast<int>(col);
            }
        }
    }

    // Scalar Test
    {
        const Mat2x2f result = matrixB / 2.0f;

        const Mat2x2f correctResult{
            1.f / 2.f,  5.f / 2.f,
            -7.f / 2.f,  3.f / 2.f
        };

        for (uint8_t row = 0; row < result.getRows(); ++row) {
            for (uint8_t col = 0; col < result.getColumns(); ++col) {
                ASSERT_NEAR(result(row, col), correctResult(row, col), 0.01f)
                    << "row = " << static_cast<int>(row) << "\n"
                    << "col = " << static_cast<int>(col);
            }
        }
    }
}

} // Math
} // lug
