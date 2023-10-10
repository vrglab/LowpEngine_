using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LowpEngine.Types.Mathmatics
{
    public class Matrix
    {
        private float[,] data;
        public int Rows { get { return data.GetLength(0); } }
        public int Columns { get { return data.GetLength(1); } }

        public float this[int i, int k] { get { return data[i, k]; }  set { data[i,k] = value; } }

        public Matrix(int xSize, int ySize)
        {
            data = new float[xSize, ySize];
        }

        public Matrix() : this(16, 16) { }

        // Matrix addition
        public static Matrix operator +(Matrix a, Matrix b)
        {
            if (a.Rows != b.Rows || a.Columns != b.Columns)
                throw new InvalidOperationException("Matrix dimensions must match for addition.");

            Matrix result = new Matrix(a.Rows, a.Columns);

            for (int i = 0; i < a.Rows; i++)
            {
                for (int j = 0; j < a.Columns; j++)
                {
                    result[i, j] = a[i, j] + b[i, j];
                }
            }

            return result;
        }

        // Matrix subtraction
        public static Matrix operator -(Matrix a, Matrix b)
        {
            if (a.Rows != b.Rows || a.Columns != b.Columns)
                throw new InvalidOperationException("Matrix dimensions must match for subtraction.");

            Matrix result = new Matrix(a.Rows, a.Columns);

            for (int i = 0; i < a.Rows; i++)
            {
                for (int j = 0; j < a.Columns; j++)
                {
                    result[i, j] = a[i, j] - b[i, j];
                }
            }

            return result;
        }

        // Scalar multiplication
        public static Matrix operator *(Matrix matrix, float scalar)
        {
            Matrix result = new Matrix(matrix.Rows, matrix.Columns);

            for (int i = 0; i < matrix.Rows; i++)
            {
                for (int j = 0; j < matrix.Columns; j++)
                {
                    result[i, j] = matrix[i, j] * scalar;
                }
            }

            return result;
        }

        // Matrix multiplication
        public static Matrix operator *(Matrix a, Matrix b)
        {
            if (a.Columns != b.Rows)
                throw new InvalidOperationException("Matrix dimensions are not compatible for multiplication.");

            Matrix result = new Matrix(a.Rows, b.Columns);

            for (int i = 0; i < a.Rows; i++)
            {
                for (int j = 0; j < b.Columns; j++)
                {
                    float sum = 0;
                    for (int k = 0; k < a.Columns; k++)
                    {
                        sum += a[i, k] * b[k, j];
                    }
                    result[i, j] = sum;
                }
            }

            return result;
        }

        // Transpose the matrix
        /// <summary>
        /// Transposes the matrix
        /// </summary>
        /// <returns>The transposed <see cref="Matrix"/></returns>
        /// <b>Authors</b>
        /// <b>Arad Bozorgmehr (Vrglab)</b>
        public Matrix Transpose()
        {
            Matrix result = new Matrix(Columns, Rows);

            for (int i = 0; i < Rows; i++)
            {
                for (int j = 0; j < Columns; j++)
                {
                    result[j, i] = this[i, j];
                }
            }

            return result;
        }

        // Determinant of a square matrix
        /// <summary>
        /// Determinant calculations
        /// </summary>
        /// <returns>The determinant of a <see cref="Matrix"/></returns>
        /// <exception cref="InvalidOperationException"></exception>
        /// <b>Authors</b>
        /// <b>Arad Bozorgmehr (Vrglab)</b>
        public float Determinant()
        {
            if (Rows != Columns)
                throw new InvalidOperationException("Determinant can only be calculated for square matrices.");

            if (Rows == 1)
            {
                return this[0, 0];
            }
            else if (Rows == 2)
            {
                return this[0, 0] * this[1, 1] - this[0, 1] * this[1, 0];
            }
            else
            {
                float det = 0;
                for (int j = 0; j < Columns; j++)
                {
                    det += this[0, j] * Cofactor(0, j);
                }
                return det;
            }
        }

        // Inverse of a square matrix
        /// <summary>
        /// The inverse calculator for the <see cref="Matrix"/>
        /// </summary>
        /// <returns>The calculated inverse <see cref="Matrix"/></returns>
        /// <exception cref="InvalidOperationException"></exception>
        /// <b>Authors</b>
        /// <b>Arad Bozorgmehr (Vrglab)</b>
        public Matrix Inverse()
        {
            if (Rows != Columns)
                throw new InvalidOperationException("Inverse can only be calculated for square matrices.");

            float det = Determinant();
            if (Math.Abs(det) < 1e-6f)
                throw new InvalidOperationException("Matrix is singular; its determinant is zero.");

            int n = Rows;
            Matrix adjugate = new Matrix(n, n);

            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    adjugate[i, j] = Cofactor(j, i) / det;
                }
            }

            return adjugate;
        }

        // Helper method to compute the cofactor of an element
        private float Cofactor(int row, int col)
        {
            Matrix subMatrix = new Matrix(Rows - 1, Columns - 1);
            int rowIndex = 0, colIndex = 0;

            for (int i = 0; i < Rows; i++)
            {
                if (i == row) continue;

                colIndex = 0;
                for (int j = 0; j < Columns; j++)
                {
                    if (j == col) continue;

                    subMatrix[rowIndex, colIndex] = this[i, j];
                    colIndex++;
                }

                rowIndex++;
            }

            float sign = (row + col) % 2 == 0 ? 1 : -1;
            return sign * subMatrix.Determinant();
        }

        // Create a translation matrix for 2D transformations
        /// <summary>
        /// 2D Translation calucator
        /// </summary>
        /// <param name="dx">The x</param>
        /// <param name="dy">The y</param>
        /// <returns>The transformed <see cref="Matrix"/></returns>
        /// <b>Authors</b>
        /// <b>Arad Bozorgmehr (Vrglab)</b>
        public static Matrix Translation2D(float dx, float dy)
        {
            Matrix translationMatrix = new Matrix(3, 3);
            translationMatrix[0, 0] = 1;
            translationMatrix[1, 1] = 1;
            translationMatrix[2, 2] = 1;
            translationMatrix[0, 2] = dx;
            translationMatrix[1, 2] = dy;

            return translationMatrix;
        }

        // Create a scaling matrix for 2D transformations
        /// <summary>
        /// Calculates the 2D scale matrix
        /// </summary>
        /// <param name="scaleX">The x</param>
        /// <param name="scaleY">The y</param>
        /// <returns>The Scaled <see cref="Matrix"/></returns>
        /// <b>Authors</b>
        /// <b>Arad Bozorgmehr (Vrglab)</b>
        public static Matrix Scaling2D(float scaleX, float scaleY)
        {
            Matrix scalingMatrix = new Matrix(3, 3);
            scalingMatrix[0, 0] = scaleX;
            scalingMatrix[1, 1] = scaleY;
            scalingMatrix[2, 2] = 1;

            return scalingMatrix;
        }

        // Create a rotation matrix for 2D transformations (in radians)
        /// <summary>
        /// Calculates the 2D rotation <see cref="Matrix"/> using the given <see cref="Quaternion"/>
        /// </summary>
        /// <param name="rotationQuaternion"></param>
        /// <returns>The created rotation <see cref="Matrix"/></returns>
        /// <b>Authors</b>
        /// <b>Arad Bozorgmehr (Vrglab)</b>
        public static Matrix Rotation2D(Quaternion rotationQuaternion)
        {

            // Convert the quaternion to a rotation matrix
            Matrix rotationMatrix = new Matrix(3, 3);

            float xx = rotationQuaternion.x * rotationQuaternion.x;
            float xy = rotationQuaternion.x * rotationQuaternion.y;

            float yy = rotationQuaternion.y * rotationQuaternion.y;

            float zz = rotationQuaternion.z * rotationQuaternion.z;
            float zw = rotationQuaternion.z * rotationQuaternion.w;

            rotationMatrix[0, 0] = 1 - 2 * (yy + zz);
            rotationMatrix[0, 1] = 2 * (xy - zw);
            rotationMatrix[0, 2] = 0;

            rotationMatrix[1, 0] = 2 * (xy + zw);
            rotationMatrix[1, 1] = 1 - 2 * (xx + zz);
            rotationMatrix[1, 2] = 0;

            rotationMatrix[2, 0] = 0;
            rotationMatrix[2, 1] = 0;
            rotationMatrix[2, 2] = 1;

            return rotationMatrix;
        }

        /// <summary>
        /// Apply's the given 2D transfomation <see cref="Matrix"/> to itself
        /// </summary>
        /// <param name="transformationMatrix">The Give <see cref="Matrix"/></param>
        /// <exception cref="InvalidOperationException"></exception>
        /// <b>Authors</b>
        /// <b>Arad Bozorgmehr (Vrglab)</b>
        public void ApplyTransformation2D(Matrix transformationMatrix)
        {
            if (Rows != 3 || Columns != 3)
                throw new InvalidOperationException("2D transformations can only be applied to 3x3 matrices.");

            this.data = (transformationMatrix * this).data;
        }



        // Create a translation matrix for 3D transformations
        /// <summary>
        /// 3D Translation calucator
        /// </summary>
        /// <param name="dx">The x</param>
        /// <param name="dy">The y</param>
        /// <param name="dz">The z</param>
        /// <returns>The transformed <see cref="Matrix"/></returns>
        /// <b>Authors</b>
        /// <b>Arad Bozorgmehr (Vrglab)</b>
        public static Matrix Translation3D(float dx, float dy, float dz)
        {
            Matrix translationMatrix = new Matrix(4, 4);
            translationMatrix[0, 0] = 1;
            translationMatrix[1, 1] = 1;
            translationMatrix[2, 2] = 1;
            translationMatrix[3, 3] = 1;
            translationMatrix[0, 3] = dx;
            translationMatrix[1, 3] = dy;
            translationMatrix[2, 3] = dz;

            return translationMatrix;
        }

        // Create a scaling matrix for 3D transformations
        /// <summary>
        /// Calculates the 3D scale matrix
        /// </summary>
        /// <param name="scaleX">The x</param>
        /// <param name="scaleY">The y</param>
        /// <param name="scaleZ">The z</param>
        /// <returns>The Scaled <see cref="Matrix"/></returns>
        /// <b>Authors</b>
        /// <b>Arad Bozorgmehr (Vrglab)</b>
        public static Matrix Scaling3D(float scaleX, float scaleY, float scaleZ)
        {
            Matrix scalingMatrix = new Matrix(4, 4);
            scalingMatrix[0, 0] = scaleX;
            scalingMatrix[1, 1] = scaleY;
            scalingMatrix[2, 2] = scaleZ;
            scalingMatrix[3, 3] = 1;

            return scalingMatrix;
        }

        // Create a 3D rotation matrix using a quaternion
        /// <summary>
        /// Calculates the 3D rotation <see cref="Matrix"/> using the given <see cref="Quaternion"/>
        /// </summary>
        /// <param name="rotationQuaternion"></param>
        /// <returns>The created rotation <see cref="Matrix"/></returns>
        /// <b>Authors</b>
        /// <b>Arad Bozorgmehr (Vrglab)</b>
        public static Matrix RotationQuaternion(Quaternion rotationQuaternion)
        {
            if (rotationQuaternion.LengthSquared() == 0)
                throw new InvalidOperationException("Invalid rotation quaternion.");

            Matrix rotationMatrix = new Matrix(4, 4);

            // Normalize the quaternion to ensure it represents a valid rotation
            rotationQuaternion.Normalize();

            // Extract rotation components from the quaternion
            float xx = rotationQuaternion.x * rotationQuaternion.x;
            float xy = rotationQuaternion.x * rotationQuaternion.y;
            float xz = rotationQuaternion.x * rotationQuaternion.z;
            float xw = rotationQuaternion.x * rotationQuaternion.w;

            float yy = rotationQuaternion.y * rotationQuaternion.y;
            float yz = rotationQuaternion.y * rotationQuaternion.z;
            float yw = rotationQuaternion.y * rotationQuaternion.w;

            float zz = rotationQuaternion.z * rotationQuaternion.z;
            float zw = rotationQuaternion.z * rotationQuaternion.w;

            // Calculate the rotation matrix
            rotationMatrix[0, 0] = 1 - 2 * (yy + zz);
            rotationMatrix[0, 1] = 2 * (xy - zw);
            rotationMatrix[0, 2] = 2 * (xz + yw);
            rotationMatrix[0, 3] = 0;

            rotationMatrix[1, 0] = 2 * (xy + zw);
            rotationMatrix[1, 1] = 1 - 2 * (xx + zz);
            rotationMatrix[1, 2] = 2 * (yz - xw);
            rotationMatrix[1, 3] = 0;

            rotationMatrix[2, 0] = 2 * (xz - yw);
            rotationMatrix[2, 1] = 2 * (yz + xw);
            rotationMatrix[2, 2] = 1 - 2 * (xx + yy);
            rotationMatrix[2, 3] = 0;

            rotationMatrix[3, 0] = 0;
            rotationMatrix[3, 1] = 0;
            rotationMatrix[3, 2] = 0;
            rotationMatrix[3, 3] = 1;

            return rotationMatrix;
        }

        /// <summary>
        /// Apply's the given 3D transfomation <see cref="Matrix"/> to itself
        /// </summary>
        /// <param name="transformationMatrix">The Give <see cref="Matrix"/></param>
        /// <exception cref="InvalidOperationException"></exception>
        /// <b>Authors</b>
        /// <b>Arad Bozorgmehr (Vrglab)</b>
        public void ApplyTransformation3D(Matrix transformationMatrix)
        {
            if (Rows != 4 || Columns != 4)
                throw new InvalidOperationException("3D transformations can only be applied to 4x4 matrices.");

            this.data = (transformationMatrix * this).data;
        }
    } 
}
