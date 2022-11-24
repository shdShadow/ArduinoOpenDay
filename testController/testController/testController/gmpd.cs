using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System;
using SharpDX.XInput;
using Microsoft.Xna.Framework;

namespace testController
{
    internal class gmpd
    {
        Controller ctrl;
        State state;
        public gmpd(UserIndex numPlayer)
        {
            ctrl = new Controller(numPlayer);
        }

        public short getLeftTriggerValue()
        {
            if (ctrl.IsConnected)
            {
                state = ctrl.GetState();
                return state.Gamepad.LeftTrigger;
            }
            else
                throw new ControllerDisconnectedException();
        }
        public short getRightTriggerValue()
        {
            if (ctrl.IsConnected)
            {
                state = ctrl.GetState();
                return state.Gamepad.RightTrigger;
            }
            else
                throw new ControllerDisconnectedException();
        }

        public bool isRBPressed()
        {
            if (ctrl.IsConnected)
            {
                state = ctrl.GetState();
                return state.Gamepad.Buttons.HasFlag(GamepadButtonFlags.RightShoulder);
            }
            else
                throw new ControllerDisconnectedException();
        }


        public bool isLBPressed()
        {
            if (ctrl.IsConnected)
            {
                state = ctrl.GetState();
                return state.Gamepad.Buttons.HasFlag(GamepadButtonFlags.LeftShoulder);
            }
            else
                throw new ControllerDisconnectedException();
        }
    }

    public class ControllerDisconnectedException : Exception
    {
        public ControllerDisconnectedException() { }
        public ControllerDisconnectedException(string message) : base(message) { }
        public ControllerDisconnectedException(string message, Exception inner) : base(message, inner) { }
    }
}
