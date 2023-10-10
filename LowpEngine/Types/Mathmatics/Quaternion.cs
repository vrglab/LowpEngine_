using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LowpEngine.Types.Mathmatics
{
    public class Quaternion
    {

        private float X,Y,Z,W;

        public float x { get => X;  set => X = value; }
        public float y { get => Y; set => Y = value; }
        public float z { get => Z; set => Z = value; }
        public float w { get => W; set => W = value; }

        public Quaternion()
        {
            X = 0;
            Y = 0;
            Z = 0;
            W = 1;
        }

        public Quaternion(float x, float y, float z, float w)
        {
            this.x = x;
            this.y = y;
            this.z = z;
            this.w = w;
        }

        // Quaternion multiplication
        public static Quaternion operator *(Quaternion q1, Quaternion q2)
        {
            float qx = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
            float qy = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
            float qz = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;
            float qw = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;

            return new Quaternion(qx, qy, qz, qw);
        }

        // Conjugate the quaternion
        /// <summary>
        /// Conjugator for the <see cref="Quaternion"/>
        /// </summary>
        /// <returns>The Conjugated <see cref="Quaternion"/></returns>
        /// <b>Authors</b>
        /// <b>Arad Bozorgmehr (Vrglab)</b>
        public Quaternion Conjugate()
        {
            return new Quaternion(-x, -y, -z, w);
        }

        // Get the magnitude (norm) of the quaternion
        /// <summary>
        /// Magnitude calculator for <see cref="Quaternion"/>
        /// </summary>
        /// <returns>The Mganitude of the <see cref="Quaternion"/></returns>
        /// <b>Authors</b>
        /// <b>Arad Bozorgmehr (Vrglab)</b>
        public float Magnitude()
        {
            return (float)Math.Sqrt(x * x + y * y + z * z + w * w);
        }

        // Normalize the quaternion
        /// <summary>
        /// Normalizes the <see cref="Quaternion"/> data
        /// </summary>
        /// <b>Authors</b>
        /// <b>Arad Bozorgmehr (Vrglab)</b>
        public void Normalize()
        {
            float magnitude = Magnitude();
            x /= magnitude;
            y /= magnitude;
            z /= magnitude;
            w /= magnitude;
        }

        // Invert the quaternion (assuming it's unit length)
        public Quaternion Inverse()
        {
            float norm = Magnitude();
            norm *= norm; // Square of the magnitude

            return new Quaternion(-x / norm, -y / norm, -z / norm, w / norm);
        }

        // Convert the quaternion to Euler angles (yaw, pitch, roll)
        /// <summary>
        /// Parses the <see cref="Quaternion"/> to a <see cref="Vector3"/> Euler Angles
        /// </summary>
        /// <returns>The calculated Eular Angles in a <see cref="Vector3"/></returns>
        /// <b>Authors</b>
        /// <b>Arad Bozorgmehr (Vrglab)</b>
        public Vector3 ToEulerAngles()
        {
            float sinr_cosp = 2 * (w * x + y * z);
            float cosr_cosp = 1 - 2 * (x * x + y * y);
            float roll = (float)Math.Atan2(sinr_cosp, cosr_cosp);

            float sinp = 2 * (w * y - z * x);
            float pitch;
            if (Math.Abs(sinp) >= 1)
            {
                pitch = (float)Math.PI / 2 * Math.Sign(sinp);
            }
            else
            {
                pitch = (float)Math.Asin(sinp);
            }

            float siny_cosp = 2 * (w * z + x * y);
            float cosy_cosp = 1 - 2 * (y * y + z * z);
            float yaw = (float)Math.Atan2(siny_cosp, cosy_cosp);

            return new Vector3(yaw, pitch, roll);
        }

        // Create a quaternion from Euler angles (yaw, pitch, roll)
        /// <summary>
        /// Parses the Eular Angles to a <see cref="Quaternion"/>
        /// </summary>
        /// <param name="yaw">The Eular Yaw</param>
        /// <param name="pitch">The Eular Pitch</param>
        /// <param name="roll">The Eular Roll</param>
        /// <returns>The calculated <see cref="Quaternion"/></returns>
        /// <b>Authors</b>
        /// <b>Arad Bozorgmehr (Vrglab)</b>
        public static Quaternion FromEulerAngles(float yaw, float pitch, float roll)
        {
            float cy = (float)Math.Cos(yaw * 0.5f);
            float sy = (float)Math.Sin(yaw * 0.5f);
            float cp = (float)Math.Cos(pitch * 0.5f);
            float sp = (float)Math.Sin(pitch * 0.5f);
            float cr = (float)Math.Cos(roll * 0.5f);
            float sr = (float)Math.Sin(roll * 0.5f);

            float w = cy * cp * cr + sy * sp * sr;
            float x = cy * cp * sr - sy * sp * cr;
            float y = sy * cp * sr + cy * sp * cr;
            float z = sy * cp * cr - cy * sp * sr;

            return new Quaternion(x, y, z, w);
        }

        /// <summary>
        /// Squared Length calculator for <see cref="Quaternion"/>
        /// </summary>
        /// <returns>The squared length (squared magnitude)</returns>
        /// <b>Authors</b>
        /// <b>Arad Bozorgmehr (Vrglab)</b>
        public float LengthSquared()
        {
            return x * x + y * y + z * z + w * w;
        }
    }
}
