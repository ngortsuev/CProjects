using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Euler
{
    //-----------------------------------------------------------------------------------------------
    // Класс для решения уравнения методом Эйлера
    // dy/dt = g(x)
    class DiffCalc
    {
        private float x, xmax, y, dx, n;
        private float slope, change;

        private void init()
        {
            x = 1;
            xmax = 2;
            y = 1;
            dx = 0.05f;
            n = (xmax - x) / dx;
        }

        public void calculate()
        {

            init();

            for (int i = 0; i < n; i++)
            {
                slope = 2 * x;

                change = slope * dx;

                y = y + change;

                x = x + dx;

                System.Console.WriteLine("x={0}:  y={1}", x, y);
            }
        }        
    }

    //-----------------------------------------------------------------------------------------------
    //Класс для решения уравнения теплопроводности dT/dt = -r(T - Ts) методом Эйлера
    /* T - температура тела
     * Ts - температура окружающей среды
     * t - время
     * r- коэффициент остывания
     * 
     * Метод Эйлера (метод касательных) сводится к замене диф. ур. -  
     *      конечно-разностной схемой: 
     *          у(x1) = y(x0) + g(x0) * delta(x); 
     *          x1 = x0 + delta(x);  
     *      g(x) - наше уравнение теплопроводности
    */
    class CoolCalc {

        private float t, dt, tmax, temperature, root_temp, r, ncalc;
        private float change;

        private void init() {
            t = 0;              //начальное время
            temperature = 83;   //начальная температура кофе (С)
            root_temp = 22;     //комнатная температура (С)
            r = 0.1f;           //коэффициент остывания (1/мин)    
            dt = 0.1f;          //шаг по времени (мин)
            tmax = 5;           //длительность (мин)
            ncalc = tmax / dt;  //общее кол-во шагов
        }

        public void calculate() {

            init();

            for(int i = 1; i < ncalc;  i ++)
            {
                change = -r * (temperature - root_temp);

                temperature = temperature + change * dt;

                t = t + dt;

                Console.WriteLine("t={0}: temperature={1}", t, temperature);
            }
        }
    }

    //-----------------------------------------------------------------------------------------------
    /* Решение уравнения заряда конденсатора R * (dQ/dt) = V - Q/C
     * R - сопротивление
     * V - напряжение
     * С - емкость
     * t - время
     * 
    */
    class KondensatorCalc
    {
        private double t, dt, tmax, ncalc;
        private double r, q, v, c;

        private void init() {
            t = 0;
            r = 2000;
            q = 0;
            v = 10;
            c = Math.Pow(10,-6);
        }

        private void calculate() {


        }
    }

    //-----------------------------------------------------------------------------------------------
    class Program
    {
        static void Main(string[] args)
        {
            CoolCalc calc = new CoolCalc();
            calc.calculate();

            Console.ReadLine();
        }
    }
}
