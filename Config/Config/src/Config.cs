using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Config
{
    internal class Configuration
    {
        private enum LightShadowLevel
        {
            NONE,
            NORMAL,
            HIGH
        };

        private bool useMultiSample = true;
        private bool useVerticalAsync = true;
        private LightShadowLevel lightShadowLevel = LightShadowLevel.HIGH;

        public Configuration()
        {
        }

        public void Load()
        {
        }
    }
}