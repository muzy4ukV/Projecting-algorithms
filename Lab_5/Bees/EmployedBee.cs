using System;
using System.Collections.Generic;
using System.Text;
using PA_Lab5.NodeStructures;
using System.Linq;
using PA_Lab5.BeeColonies;

namespace PA_Lab5.Bees
{
    class EmployedBee : IBee
    {
        private BeeColony _colony;
        private SubGraph _subGraph;
        public EmployedBee(BeeColony colony)
        {
            _colony = colony;
        }

        public SubGraph GetLocation()
        {
            return _subGraph;
        }

        public void PickArea(int size)
        {
            List<Node> tempSolution = new List<Node>();
            tempSolution.Add(PickNode(_colony.GetSearchArea().GetNodes()));

            while (tempSolution.Count != size)
            {
                int i = 0;
                Node goal;
                do
                {
                    goal = null;
                    i++;
                    var tempNode = tempSolution[tempSolution.Count - i];
                    goal = PickNode(tempNode.GetAdjacents().Where(a => !tempSolution.Contains(a)).ToList());
                } while (tempSolution.Contains(goal));
                tempSolution.Add(goal);
            }

            int counter = 0;
            foreach (var a in tempSolution)
            {
                foreach (var b in tempSolution)
                {
                    if (a.Identificator == b.Identificator) counter++;
                }
            }
            if (counter > size) throw new Exception();
            _subGraph = new SubGraph(tempSolution);
            _subGraph.AddDescendants(_subGraph.AnalyzeAdjacentCommonNodes().ToList());
        }

        public Node PickNode(List<Node> nodes)
        {
            var cumulativeNectar = 0;
            foreach (var node in nodes)
            {
                cumulativeNectar += node.GetAdjacents().Count;
            }

            Dictionary<Node, double> chances = new Dictionary<Node, double>();
            foreach (var node in nodes)
            {
                chances.Add(node, (double)node.GetAdjacents().Count / (double)cumulativeNectar);
            }

            chances.OrderBy(a => a.Value);
            var cumulativeChance = 0D;
            Random rand = new Random();

            var chance = rand.NextDouble();

            foreach (var probability in chances)
            {
                if (chance > cumulativeChance && chance < (cumulativeChance + probability.Value))
                {
                    return probability.Key;
                }
                cumulativeChance += probability.Value;
            }

            return null;
        }
    }
}
