using System;
using System.Collections.Generic;
using PA_Lab5.Bees;
using PA_Lab5.BeeColonies;
using PA_Lab5.NodeStructures;
using System.Diagnostics;
using System.Linq;

namespace BetterOne
{
    class Program
    {
        static void Main(string[] args)
        {
            Graph graph = new Graph(GenerateNodes(200));

            Console.WriteLine("Welcome to bee algorithm for clique-searching");

            Console.WriteLine("Please, enter the bee number (for instance, 100)\n");

            int beeCount = -1;
            
            var tempValue = Console.ReadLine();

            while (!Int32.TryParse(tempValue, out beeCount) || beeCount < 10)
            {
                Console.WriteLine("Please, enter the correct value");
                tempValue = Console.ReadLine();
            }
            
            
            Console.WriteLine("Value accepted. Now enter clique size:\n(Warning, occurence of clique sized more than 5 is unlikely)\n");

            int cliqueSize = 0;
            
            tempValue = Console.ReadLine();

            while (!Int32.TryParse(tempValue, out cliqueSize) || cliqueSize <1)
            {
                Console.WriteLine("Please, enter the correct value");
                tempValue = Console.ReadLine();
            }
            

            double dilyankyCoefficient = -1;

            Console.WriteLine("Now enter the portion of areas in the memory of colony to be saved:");
            
            while (!Double.TryParse(tempValue, out dilyankyCoefficient)||(dilyankyCoefficient <= 0 || dilyankyCoefficient > 1))
            {
                Console.WriteLine("Please, enter the correct value (for instance 0,4 ))\n");
                tempValue = Console.ReadLine();
            }
            
            BeeColony beeColony = new BeeColony(graph, cliqueSize,dilyankyCoefficient);

            var employedBees = GenerateEmployedBees((int)(beeCount*0.1), beeColony);
            var onlookerBees = GenerateOnlookerBees(beeCount - employedBees.Count, beeColony);


            beeColony.SetBees(employedBees,onlookerBees);

          
            Console.WriteLine("Great! Everything is ready\nExecuting order 66....");

            beeColony.SetBees(employedBees, onlookerBees);

            Stopwatch sw = new Stopwatch();
            sw.Start();
            var clique = beeColony.FindClique();
            sw.Stop();
            var ts = sw.Elapsed;
            Console.WriteLine("Success; Time to find: {0:00}:{1:00}:{2:00}.{3:000}", ts.Hours, ts.Minutes, ts.Seconds, ts.Milliseconds / 10);
            Console.WriteLine("Nodes and their adjacents:");
            var temp2 = clique.GetMembers();
            foreach (var member in temp2)
            {
                Console.WriteLine("Member identificator:{0}", member.Identificator);
                Console.Write("Adjacents: ");
                foreach (var a in member.GetAdjacents())
                {
                    Console.Write("{0} ", a.Identificator);
                }
                Console.WriteLine('\n');
            }


        }
        public static List<Node> GenerateNodes(int size)
        {
            var tempList = new List<Node>();
            for (int i = 0; i < size; i++)
            {
                tempList.Add(new Node(i));
            }
            return tempList;
        }

        public static List<EmployedBee> GenerateEmployedBees(int count, BeeColony colony)
        {
            var bees = new List<EmployedBee>();

            for (int i = 0; i < count; i++)
            {
                bees.Add(new EmployedBee(colony));
            }

            return bees;
        }

        public static List<OnlookerBee> GenerateOnlookerBees(int count, BeeColony colony)
        {
            var bees = new List<OnlookerBee>();

            for (int i = 0; i < count; i++)
            {
                bees.Add(new OnlookerBee(colony));
            }
            return bees;
        }
    }
}
