using System;
using System.Xml;

class Program
{
    static void Main()
    {
        string[] Projects = { "TestProject" };

        string[] IncludeDirectorys = { "TestDir1", "TestDir2" };

        //string[] Projects = { "HyIOCP", "Client", "Server" };

        string binDirectory = AppDomain.CurrentDomain.BaseDirectory;
        string absolutePath = System.IO.Path.GetFullPath(binDirectory);
        string solutionPath = RemoveLastDirectory(absolutePath, 7);
        

        for (int i = 0; i < Projects.Length; i++)
        {
            string project = Projects[i];
            string absoluteProjectPath = solutionPath + "\\" + project + "\\" + project + ".vcxproj";
            Console.WriteLine(absoluteProjectPath);


            for(int j = 0; j < IncludeDirectorys.Length; j++)
            {
                string includeDir = solutionPath + IncludeDirectorys[j];

                AddIncludeDirectory(solutionPath, absoluteProjectPath, includeDir);

            }
        }

    }
    public static string RemoveLastDirectory(string path, int rmLen)
    {
        // 경로를 디렉토리로 분할
        string[] directories = path.Split(System.IO.Path.DirectorySeparatorChar);

        // 경로에서 마지막 디렉토리 제거
        string[] newPathArray = new string[directories.Length - rmLen];
        Array.Copy(directories, newPathArray, directories.Length - rmLen);

        // 새로운 경로 반환
        return string.Join(System.IO.Path.DirectorySeparatorChar.ToString(), newPathArray);
    }

    static void AddIncludeDirectory(string solutionFilePath, string projectFilePath, string includeDirectory)
    {
        // Load the project file
        XmlDocument doc = new XmlDocument();
        doc.Load(projectFilePath);

        // Find the <ItemDefinitionGroup> element under <Project> element
        XmlNodeList itemDefGroups = doc.GetElementsByTagName("ItemDefinitionGroup");
        XmlNode itemDefGroup = null;
        foreach (XmlNode node in itemDefGroups)
        {
            if (node.ParentNode.Name == "Project")
            {
                itemDefGroup = node;
                break;
            }
        }

        if (itemDefGroup != null)
        {
            // Create a new <AdditionalIncludeDirectories> element
            XmlElement includeElem = doc.CreateElement("AdditionalIncludeDirectories");
            includeElem.InnerText = "$(SolutionDir)" + includeDirectory + ";%(AdditionalIncludeDirectories)";

            // Create a new <ClCompile> element
            XmlElement clCompileElem = doc.CreateElement("ClCompile", doc.DocumentElement.NamespaceURI);
            clCompileElem.AppendChild(includeElem);

            // Append the <ClCompile> element to <ItemDefinitionGroup>
            itemDefGroup.AppendChild(clCompileElem);
        }

        // Save the modified XML back to the project file
        doc.Save(projectFilePath);
    }
}