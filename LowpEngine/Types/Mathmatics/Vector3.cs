using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;

namespace LowpEngine.Types.Mathmatics
{
    public class Vector3
    {
        private float X, Y, Z;
        public float x { get => X; set => X = value; }
        public float y { get => Y; set => Y = value; }
        public float z { get => Z; set => Z = value; }

        public Vector3()
        {
            X = 0;
            Y = 0;
            Z = 0;
        }

        public Vector3(float x, float y, float z)
        {
            this.x = x;
            this.y = y;
            this.z = z;
        }

        // Vector addition
        public static Vector3 operator +(Vector3 v1, Vector3 v2)
        {
            return new Vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
        }

        // Vector subtraction
        public static Vector3 operator -(Vector3 v1, Vector3 v2)
        {
            return new Vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
        }

        // Scalar multiplication
        public static Vector3 operator *(Vector3 v, float scalar)
        {
            return new Vector3(v.x * scalar, v.y * scalar, v.z * scalar);
        }

        // Scalar division
        public static Vector3 operator /(Vector3 v, float scalar)
        {
            if (Math.Abs(scalar) < 1e-6f)
                throw new InvalidOperationException("Division by zero or very small value.");

            return new Vector3(v.x / scalar, v.y / scalar, v.z / scalar);
        }

        // Dot product of two vectors
        /// <summary>
        /// Dot product calculator for <see cref="Vector3"/>
        /// </summary>
        /// <param name="v1">First Vector</param>
        /// <param name="v2">Second Vector</param>
        /// <returns>The Dot product</returns>
        /// <b>Authors</b>
        /// <b>Arad Bozorgmehr (Vrglab)</b>
        public static float Dot(Vector3 v1, Vector3 v2)
        {
            return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
        }

        // Cross product of two vectors
        /// <summary>
        /// Cross product claculator for <see cref="Vector3"/>
        /// </summary>
        /// <param name="v1"></param>
        /// <param name="v2"></param>
        /// <returns>The Cross product</returns>
        /// <b>Authors</b>
        /// <b>Arad Bozorgmehr (Vrglab)</b>
        public static Vector3 Cross(Vector3 v1, Vector3 v2)
        {
            return new Vector3(
                v1.y * v2.z - v1.z * v2.y,
                v1.z * v2.x - v1.x * v2.z,
                v1.x * v2.y - v1.y * v2.x
            );
        }

        // Calculate the magnitude (norm) of the vector
        /// <summary>
        /// Magnitude calculator for <see cref="Vector3"/>
        /// </summary>
        /// <returns>The Mganitude of the <see cref="Vector3"/></returns>
        /// <b>Authors</b>
        /// <b>Arad Bozorgmehr (Vrglab)</b>
        public float Magnitude()
        {
            return (float)Math.Sqrt(x * x + y * y + z * z);
        }

        // Normalize the vector
        /// <summary>
        /// Normalizes the <see cref="Vector3"/> data
        /// </summary>
        /// <exception cref="InvalidOperationException"></exception>
        /// <b>Authors</b>
        /// <b>Arad Bozorgmehr (Vrglab)</b>
        public void Normalize()
        {
            float magnitude = Magnitude();
            if (Math.Abs(magnitude) < 1e-6f)
                throw new InvalidOperationException("Normalization of a zero-length vector is not defined.");

            x /= magnitude;
            y /= magnitude;
            z /= magnitude;
        }
    }
}
