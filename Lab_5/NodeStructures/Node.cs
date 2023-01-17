using System;
using System.Collections.Generic;
using System.Text;

namespace PA_Lab5.NodeStructures
{
    class Node
    {
        public int Identificator
        {
            get;
            private set;
        }
        private List<Node> _adjacetns;

        public Node(int identificator)
        {
            Identificator = identificator;
        }

        public void SetAdjacents(List<Node> adjacents)
        {
            _adjacetns = adjacents;
        }

        public List<Node> GetAdjacents()
        {
            return _adjacetns;
        }

        public void AddAdjecent(Node node)
        {
            _adjacetns.Add(node);
        }
    }
}
