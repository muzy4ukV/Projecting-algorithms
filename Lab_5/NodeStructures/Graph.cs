using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;

namespace PA_Lab5.NodeStructures
{
    class Graph
    {
        List<Node> _nodes;

        public Graph(List<Node> nodes)
        {
            _nodes = nodes;

            ReInitNodes();
        }

        public void ReInitNodes()
        {
            Random rand = new Random();

            foreach (var node in _nodes)
            {
                node.SetAdjacents(new List<Node>());
            }

            foreach (var node in _nodes)
            {
                var limit = rand.Next(2, 31);
                if (node.GetAdjacents().Count + limit > 31) continue;
                var tempAdjacents = _nodes.Where(a => 
                a.Identificator != node.Identificator&&
                a.GetAdjacents().Count<31
                &&!a.GetAdjacents().Contains(node)).OrderBy(_ => rand.Next()).Take(limit).ToList();

                foreach(var a in tempAdjacents)
                {
                    node.AddAdjecent(a);
                    a.AddAdjecent(node);
                }
            }
        }
        public List<Node> GetNodes()
        {
            return _nodes;
        }
    }
}
