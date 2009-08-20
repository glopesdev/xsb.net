XSBDotNet Installation
----------------------

In order to have XSBDotNet up and running:

1. Configure and build XSB in one of the available configurations
   (e.g. i686-pc-cygwin or i686-pc-cygwin-mt).

2. Copy managed.dll to XSB's config/CONFIGURATION/bin folder.

3. Copy managed.xwam to XSB's packages folder.

4. Include XsbDotNet.dll as a reference in your project and make sure to call the
InitXsb() method with the full path to XSB's root directory.

Post any difficulties and issues on the bug tracker at http://sourceforge.net/projects/xsbdotnet/.