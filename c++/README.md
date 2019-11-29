### C++

### Building the C++ example

1. Launch `Example.sln` in Visual Studio
2. Go to "Project > Example Properties > Reference Paths"
3. Add the following paths:
  + `<your 3ds Max install path>\3ds Max 2019\`
  + `<your 3ds Max install path>\3ds Max 2019\bin\assemblies\`
4. Click on to "Build > Build Solution"

### Running the C++ example

There are two ways in installing & running the C++ example:

1. Go to "x64\bin\Debug\" or "x64\bin\Release\"
2. Copy `CustomNotificationsDemo.dlu` to `<your 3ds Max install path>\3ds Max 2019\stdplugs\`
3. Launch 3ds Max 2019

**or**

1. Launch 3ds Max 2019
2. Go to "Customize > Plug-in Manager (Right Click) > Load New Plug-in..."
3. Go to "x64\bin\Debug\" or "x64\bin\Release\" and select `CustomNotificationsDemo.dlu`

Finally, go to "Utilities > More... > Custom Notifications Demo" to run the demo.

### LICENSE

Apache License 2.0

See [LICENSE](https://github.com/hako/3dsMax-CustomNotifications/tree/master/LICENSE) for the full license text.