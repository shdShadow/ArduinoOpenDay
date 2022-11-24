using System;
using System.ComponentModel.Design.Serialization;
using System.IO.Ports;
using System.Reflection.Emit;
using SharpDX.XInput;
using testController;
using Uno.Xaml;

namespace XBoxSampleConsole
{
    class Program
    {
        static SerialPort serialBluetooth = null;
        static void Main(string[] args)
        {
            string[] ports = SerialPort.GetPortNames();
            for(int i =0; i<ports.Length; i++)
            {
                Console.WriteLine(i+ ": " + ports[i]);
            }
            string p = Console.ReadLine();
            //p = ports[p];
            char c = '0';
            serialBluetooth = new SerialPort("COM"+p, 9600 );
            serialBluetooth.DataReceived += SerialBluetooth_DataReceived;
            serialBluetooth.ReadTimeout = 100;
            serialBluetooth.WriteTimeout = 100;
            serialBluetooth.Open();
            Controller ctrl = new Controller(UserIndex.One);
            State s;
            int potenza = 0;
            float percentualeDir = 0;
            int l = 0, r = 0;
            int motorePrincipale = 0, motoreSecondario = 0;
            byte sx = 0, dx = 0;
            while (ctrl.IsConnected)
            {
                s = ctrl.GetState();

                #region get valori
                potenza = s.Gamepad.RightTrigger - s.Gamepad.LeftTrigger;
                percentualeDir = s.Gamepad.LeftThumbX / (float)(s.Gamepad.LeftThumbX < 0 ? -32768 : 32767);
                //Console.WriteLine(potenza.ToString() + '\t' + percentualeDir.ToString()+ '\n');
                #endregion

                #region calcoli
                motorePrincipale = Math.Abs(potenza);
                if (potenza < 0)
                {
                    motoreSecondario = (int)(-potenza - -potenza * percentualeDir);
                    if (s.Gamepad.LeftThumbX < 0)
                    {
                        l = motorePrincipale;
                        r = motoreSecondario;
                    }
                    else if (s.Gamepad.LeftThumbX > 0)
                    {
                        l = motoreSecondario;
                        r = motorePrincipale;
                    }
                    else
                        l = r = motorePrincipale;
                    l = map(l, 0, 255, 127, 1);
                    r = map(r, 0, 255, 127, 1);
                }
                else if(potenza>0)
                {
                    motoreSecondario = (int)(potenza - potenza * percentualeDir);
                    if (s.Gamepad.LeftThumbX < 0)
                    {
                        l = motoreSecondario;
                        r = motorePrincipale;
                    }
                    else if (s.Gamepad.LeftThumbX > 0)
                    {
                        l = motorePrincipale;
                        r = motoreSecondario;
                    }
                    else
                        l = r = motorePrincipale;
                    l = map(l, 0, 255, 129, 255);
                    r = map(r, 0, 255, 129, 255);

                }
                else
                {
                    l = 128;
                    r = 128;
                }
                #endregion
                
                sx = (byte)l; dx = (byte)r;
                Console.WriteLine(sx.ToString() + "\t" + dx.ToString() + '\n');
                try
                {
                    byte[] arr = {0, (byte)sx, (byte)dx };
                    serialBluetooth.Write(arr, 0, 3);
                    //serialBluetooth.Write(new char[] { c }, 0, 1);
                    //serialBluetooth.Write("0" + t1.ToString() + t2.ToString());
                }
                catch (Exception e)
                {

                }
                Thread.Sleep(100);
            }
            serialBluetooth.Close();
        }

        private static void SerialBluetooth_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            Console.Write(serialBluetooth.ReadExisting());
        }

        private static int map(int value, int fromLow, int fromHigh, int toLow, int toHigh)
        {
            return (value - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
        }

    }
}