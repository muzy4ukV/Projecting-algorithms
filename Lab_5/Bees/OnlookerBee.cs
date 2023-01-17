using System;
using System.Collections.Generic;
using System.Text;
using PA_Lab5.NodeStructures;
using System.Linq;
using PA_Lab5.BeeColonies;

namespace PA_Lab5.Bees
{
    class OnlookerBee:IBee
    {
        private BeeColony _colony;
        private SubGraph _subGraph;

        public OnlookerBee(BeeColony colony)
        {
            _colony = colony;
        }

        public SubGraph GetLocation()
        {
            return _subGraph;
        }

        public void PickArea(int areaSize)
        {
            var sources = _colony.GetDiscoveredFoodSources().OrderBy(a => a.Item2).ToList();

            int cumulativeNectar = 0;
            int i = 0;
            foreach (var source in sources)
            {
                cumulativeNectar += source.Item2*(sources.Count-i);
                i++;
            }

            var subGraphsAndChances = new Dictionary<SubGraph, double>();
            i = 0;
            foreach (var source in sources)
            {
                subGraphsAndChances.Add(source.Item1, (double)source.Item2*(sources.Count -i) / (double)cumulativeNectar);
            }

            var rand = new Random();

            var chance = rand.NextDouble();
            double cumulativeChance = 0;
            foreach (var probability in subGraphsAndChances)
            {
                if (chance > cumulativeChance && chance < (cumulativeChance + probability.Value))
                {
                    _subGraph = probability.Key;
                    return;
                }
                cumulativeChance += probability.Value;
            }
        }

        public void DiscoverAdjacentArea(int areaSize)
        {
            if (_subGraph.GetDescendants().Count == 0) return;
            var subgraph =_subGraph.GetDescendants().First();

            _subGraph.PopDescendant(subgraph);
            _subGraph = subgraph;

            _subGraph.AddDescendants(_subGraph.AnalyzeAdjacentCommonNodes().ToList());
        }
    }
}
