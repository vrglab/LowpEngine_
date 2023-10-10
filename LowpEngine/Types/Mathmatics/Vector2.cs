using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LowpEngine.Types.Mathmatics
{
    public class Vector2
    {
        private float X, Y;

        public float x { get => X; set => X = value; }
        public float y { get => Y; set => Y = value; }

        public Vector2()
        {
            X = 0;
            Y = 0;
        }

        public Vector2(float x, float y)
        {
            this.x = x;
            this.y = y;
        }

        // Vector addition
        public static Vector2 operator +(Vector2 v1, Vector2 v2)
        {
            return new Vector2(v1.x + v2.x, v1.y + v2.y);
        }

        // Vector subtraction
        public static Vector2 operator -(Vector2 v1, Vector2 v2)
        {
            return new Vector2(v1.x - v2.x, v1.y - v2.y);
        }

        // Scalar multiplication
        public static Vector2 operator *(Vector2 v, float scalar)
        {
            return new Vector2(v.x * scalar, v.y * scalar);
        }

        // Scalar division
        public static Vector2 operator /(Vector2 v, float scalar)
        {
            if (Math.Abs(scalar) < 1e-6f)
                throw new InvalidOperationException("Division by zero or very small value.");

            return new Vector2(v.x / scalar, v.y / scalar);
        }

        // Dot product of two vectors
        /// <summary>
        /// Dot product calculator for <see cref="Vector2"/>
        /// </summary>
        /// <param name="v1">First Vector</param>
        /// <param name="v2">Second Vector</param>
        /// <returns>The Dot product</returns>
        /// <b>Authors</b>
        /// <b>Arad Bozorgmehr (Vrglab)</b>
        public static float Dot(Vector2 v1, Vector2 v2)
        {
            return v1.x * v2.x + v1.y * v2.y;
        }

        // Calculate the magnitude (norm) of the vector
        /// <summary>
        /// Magnitude calculator for <see cref="Vector2"/>
        /// </summary>
        /// <returns>The Mganitude of the <see cref="Vector2"/></returns>
        /// <b>Authors</b>
        /// <b>Arad Bozorgmehr (Vrglab)</b>
        public float Magnitude()
        {
            return (float)Math.Sqrt(x * x + y * y);
        }

        // Calculate the squared length (squared magnitude) of the vector
        /// <summary>
        /// Squared Length calculator for <see cref="Vector2"/>
        /// </summary>
        /// <returns>The squared length (squared magnitude)</returns>
        /// <b>Authors</b>
        /// <b>Arad Bozorgmehr (Vrglab)</b>
        public float LengthSquared()
        {
            return x * x + y * y;
        }

        // Normalize the vector
        /// <summary>
        /// Normalizes the <see cref="Vector2"/> data
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
        }
    }
}
