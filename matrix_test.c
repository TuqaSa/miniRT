/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaeed < tsaeed@student.42amman.com >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 20:00:00 by tsaeed            #+#    #+#             */
/*   Updated: 2025/09/16 23:02:14 by tsaeed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void
print_matrix (t_matrix *matrix)
{
    int i, j;

    if (!matrix)
        {
            printf ("Matrix is NULL\n");
            return;
        }

    printf ("Matrix %dx%d:\n", matrix->rows, matrix->cols);
    i = 0;
    while (i < matrix->rows)
        {
            printf ("| ");
            j = 0;
            while (j < matrix->cols)
                {
                    printf ("%6.1f ", matrix->data[i][j]);
                    j++;
                }
            printf ("|\n");
            i++;
        }
    printf ("\n");
}

void
test_4x4_matrix (void)
{
    printf ("=== Testing 4x4 Matrix (Book Example) ===\n");

    // Create the matrix from the book:
    // |  1   |  2   |  3   |  4   |
    // |  5.5 |  6.5 |  7.5 |  8.5 |
    // |  9   | 10   | 11   | 12   |
    // | 13.5 | 14.5 | 15.5 | 16.5 |

    float values[] = { 1.0f, 2.0f,  3.0f,  4.0f,  5.5f,  6.5f,  7.5f,  8.5f,
                       9.0f, 10.0f, 11.0f, 12.0f, 13.5f, 14.5f, 15.5f, 16.5f };

    t_matrix *M = matrix_from_array (4, 4, values);
    if (!M)
        {
            printf ("Failed to create 4x4 matrix\n");
            return;
        }

    print_matrix (M);

    // Test the book's assertions
    printf ("Testing matrix element access:\n");
    printf ("M[0,0] = %.1f (expected: 1)\n", matrix_get (M, 0, 0));
    printf ("M[0,3] = %.1f (expected: 4)\n", matrix_get (M, 0, 3));
    printf ("M[1,0] = %.1f (expected: 5.5)\n", matrix_get (M, 1, 0));
    printf ("M[1,2] = %.1f (expected: 7.5)\n", matrix_get (M, 1, 2));
    printf ("M[2,2] = %.1f (expected: 11)\n", matrix_get (M, 2, 2));
    printf ("M[3,0] = %.1f (expected: 13.5)\n", matrix_get (M, 3, 0));
    printf ("M[3,2] = %.1f (expected: 15.5)\n", matrix_get (M, 3, 2));

    matrix_destroy (M);
    printf ("✓ 4x4 Matrix test completed\n\n");
}

void
test_2x2_matrix (void)
{
    printf ("=== Testing 2x2 Matrix (Book Example) ===\n");

    // Create the matrix from the book:
    // | -3 |  5 |
    // |  1 | -2 |

    float values[] = { -3.0f, 5.0f, 1.0f, -2.0f };

    t_matrix *M = matrix_from_array (2, 2, values);
    if (!M)
        {
            printf ("Failed to create 2x2 matrix\n");
            return;
        }

    print_matrix (M);

    // Test the book's assertions
    printf ("Testing matrix element access:\n");
    printf ("M[0,0] = %.1f (expected: -3)\n", matrix_get (M, 0, 0));
    printf ("M[0,1] = %.1f (expected: 5)\n", matrix_get (M, 0, 1));
    printf ("M[1,0] = %.1f (expected: 1)\n", matrix_get (M, 1, 0));
    printf ("M[1,1] = %.1f (expected: -2)\n", matrix_get (M, 1, 1));

    matrix_destroy (M);
    printf ("✓ 2x2 Matrix test completed\n\n");
}

void
test_3x3_matrix (void)
{
    printf ("=== Testing 3x3 Matrix (Book Example) ===\n");

    // Create the matrix from the book:
    // | -3 |  5 |  0 |
    // |  1 | -2 | -7 |
    // |  0 |  1 |  1 |

    float values[]
        = { -3.0f, 5.0f, 0.0f, 1.0f, -2.0f, -7.0f, 0.0f, 1.0f, 1.0f };

    t_matrix *M = matrix_from_array (3, 3, values);
    if (!M)
        {
            printf ("Failed to create 3x3 matrix\n");
            return;
        }

    print_matrix (M);

    // Test the book's assertions
    printf ("Testing matrix element access:\n");
    printf ("M[0,0] = %.1f (expected: -3)\n", matrix_get (M, 0, 0));
    printf ("M[1,1] = %.1f (expected: -2)\n", matrix_get (M, 1, 1));
    printf ("M[2,2] = %.1f (expected: 1)\n", matrix_get (M, 2, 2));

    matrix_destroy (M);
    printf ("✓ 3x3 Matrix test completed\n\n");
}

void
test_matrix_creation_and_modification (void)
{
    printf ("=== Testing Matrix Creation and Modification ===\n");

    // Create an empty 3x3 matrix
    t_matrix *matrix = matrix_create (3, 3);
    if (!matrix)
        {
            printf ("Failed to create matrix\n");
            return;
        }

    printf ("Empty 3x3 matrix:\n");
    print_matrix (matrix);

    // Fill it with some values using matrix_set
    matrix_set (matrix, 0, 0, 1.0f);
    matrix_set (matrix, 0, 1, 2.0f);
    matrix_set (matrix, 0, 2, 3.0f);
    matrix_set (matrix, 1, 0, 4.0f);
    matrix_set (matrix, 1, 1, 5.0f);
    matrix_set (matrix, 1, 2, 6.0f);
    matrix_set (matrix, 2, 0, 7.0f);
    matrix_set (matrix, 2, 1, 8.0f);
    matrix_set (matrix, 2, 2, 9.0f);

    printf ("After setting values:\n");
    print_matrix (matrix);

    matrix_destroy (matrix);
    printf ("✓ Matrix creation and modification test completed\n\n");
}

int
main (void)
{
    printf ("==========================================\n");
    printf ("    Matrix Implementation Test Suite\n");
    printf ("    (Based on The Ray Tracer Challenge)\n");
    printf ("==========================================\n\n");

    test_4x4_matrix ();
    test_2x2_matrix ();
    test_3x3_matrix ();
    test_matrix_creation_and_modification ();

    printf ("==========================================\n");
    printf ("         All matrix tests completed!\n");
    printf ("==========================================\n");

    return (0);
}
