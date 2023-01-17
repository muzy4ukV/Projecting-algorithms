using System;
using System.Collections.Generic;
using System.Text;
using PA_Lab5.NodeStructures;

namespace PA_Lab5.Bees
{
    interface IBee
    {
            public void PickArea(int areaSize);
            public SubGraph GetLocation();
            
    }
}
