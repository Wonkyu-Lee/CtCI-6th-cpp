//
// Created by blazeq on 2017. 10. 12..
//

#include "catch.hpp"
#include "Graph.h"
#include <stack>

namespace ex_04_07 {

namespace solution1 {

using namespace std;

class Project
{
private:
    vector<Project*> _children;
    unordered_map<string, Project*> _map;
    string _name;
    int _dependencies{0};

public:
    Project(string name) : _name(name) {}

    void addNeighbor(Project* node)
    {
        if (_map.find(node->_name) == _map.end()) {
            _children.push_back(node);
            _map.insert(make_pair(node->_name, node));
            node->incrementDependency();
        }
    }

    void incrementDependency()
    {
        _dependencies++;
    }

    void decementDependency()
    {
        _dependencies--;
    }

    const string& getName()
    {
        return _name;
    }

    vector<Project*>& getChildren()
    {
        return _children;
    }

    int getNumberDependencides()
    {
        return _dependencies;
    }
};

class Graph
{
private:
    vector<Project*> _nodes;
    unordered_map<string, Project*> _map;

public:
    ~Graph()
    {
        for (auto node : _nodes)
            delete node;
    }

    Project* getOrCreateNode(const string& name)
    {
        auto found = _map.find(name);
        if (found == _map.end()) {
            Project* node = new Project(name);
            _nodes.push_back(node);
            _map.insert(make_pair(name, node));
            return node;
        }

        return found->second;
    }

    void addEdge(const string& startName, const string& endName)
    {
        Project* start = getOrCreateNode(startName);
        Project* end = getOrCreateNode(endName);
        start->addNeighbor(end);
    }

    vector<Project*>& getNodes()
    {
        return _nodes;
    }
};

int addNonDependent(vector<Project*>& order, vector<Project*>& projects, int endOfList)
{
    for (auto project : projects) {
        if (project->getNumberDependencides() == 0) {
            order[endOfList++] = project;
        }
    }

    return endOfList;
}

bool findBuildOrder(Graph& graph, vector<Project*>& order)
{
    auto& projects = graph.getNodes();

    order.clear();
    order.reserve(projects.size());
    order.insert(order.begin(), projects.size(), nullptr);

    int endOfList = addNonDependent(order, projects, 0);

    int toBeProcessed = 0;
    while (toBeProcessed < order.size()) {
        Project* current = order[toBeProcessed];

        if (current == nullptr) {
            order.clear();
            return false;
        }

        auto& children = current->getChildren();
        for (auto child : children) {
            child->decementDependency();
        }

        endOfList = addNonDependent(order, children, endOfList);
        toBeProcessed++;
    }

    return true;
}

using Dependency = pair<string, string>;

Graph* buildGraph(vector<string>& projects, vector<Dependency>& dependencies)
{
    Graph* graph = new Graph();

    for (auto project : projects) {
        graph->getOrCreateNode(project);
    }

    for (auto dependency : dependencies) {
        graph->addEdge(dependency.first, dependency.second);
    }

    return graph;
}

list<string> findBuildOrder(vector<string>& projects, vector<Dependency>& dependencies)
{
    Graph* g = buildGraph(projects, dependencies);

    vector<Project*> order;
    findBuildOrder(*g, order);

    list<string> result;
    for (auto project : order) {
        result.push_back(project->getName());
    }

    delete g;
    return result;
}

} // namespace solution1

namespace solution2 {

using namespace std;

class Project
{
public:
    enum class State {
        BLANK, PARTIAL, COMPLETE
    };

private:
    vector<Project*> _children;
    unordered_map<string, Project*> _map;
    string _name;
    State _state{State::BLANK};

public:
    Project(string name) : _name(name) {}

    void addNeighbor(Project* node)
    {
        if (_map.find(node->_name) == _map.end()) {
            _children.push_back(node);
            _map.insert(make_pair(node->_name, node));
        }
    }

    const string& getName()
    {
        return _name;
    }

    vector<Project*>& getChildren()
    {
        return _children;
    }

    State getState() {
        return _state;
    }

    void setState(State state) {
        _state = state;
    }
};

class Graph
{
private:
    vector<Project*> _nodes;
    unordered_map<string, Project*> _map;

public:
    ~Graph()
    {
        for (auto node : _nodes)
            delete node;
    }

    Project* getOrCreateNode(const string& name)
    {
        auto found = _map.find(name);
        if (found == _map.end()) {
            Project* node = new Project(name);
            _nodes.push_back(node);
            _map.insert(make_pair(name, node));
            return node;
        }

        return found->second;
    }

    void addEdge(const string& startName, const string& endName)
    {
        Project* start = getOrCreateNode(startName);
        Project* end = getOrCreateNode(endName);
        start->addNeighbor(end);
    }

    vector<Project*>& getNodes()
    {
        return _nodes;
    }
};

bool doDfs(Project* project, stack<Project*>& order) {
    if (project->getState() == Project::State::PARTIAL) {
        return false;
    }

    if (project->getState() == Project::State::BLANK) {
        project->setState(Project::State::PARTIAL);
        for (auto child : project->getChildren()) {
            if (!doDfs(child, order))
                return false;
        }
        project->setState(Project::State::COMPLETE);
        order.push(project);
    }

    return true;
}

bool findBuildOrder(Graph& graph, stack<Project*>& order)
{
    for (auto project : graph.getNodes()) {
        if (project->getState() == Project::State::BLANK) {
            if (!doDfs(project, order)) {
                return false;
            }
        }
    }

    return true;
}

using Dependency = pair<string, string>;

Graph* buildGraph(vector<string>& projects, vector<Dependency>& dependencies)
{
    Graph* graph = new Graph();

    for (auto project : projects) {
        graph->getOrCreateNode(project);
    }

    for (auto dependency : dependencies) {
        graph->addEdge(dependency.first, dependency.second);
    }

    return graph;
}

list<string> findBuildOrder(vector<string>& projects, vector<Dependency>& dependencies)
{
    Graph* g = buildGraph(projects, dependencies);

    list<string> result;

    stack<Project*> order;
    if (!findBuildOrder(*g, order)) {
        return result;
    }

    while (!order.empty()) {
        result.push_back(order.top()->getName());
        order.pop();
    }

    delete g;
    return result;
}

} // namespace solution2

namespace solution3 {

using namespace std;
using namespace qds;

using Dependency = pair<string, string>;

void buildGraph(Graph<string>& g, vector<string>& projects, vector<Dependency>& dependencies)
{
    for (auto project : projects) {
        g.addVertex(project);
    }

    for (auto dependency : dependencies) {
        g.addEdge(dependency.first, dependency.second);
    }
}

list<string> findBuildOrder(vector<string>& projects, vector<Dependency>& dependencies)
{
    Graph<string> g;
    buildGraph(g, projects, dependencies);
    return g.topologicalSort();
}

} // namespace solution3

TEST_CASE("04-07", "[04-07]")
{
    SECTION("Solution1") {
        using namespace solution1;

        SECTION("Project order exists") {
            vector<string> projects{"a", "b", "c", "d", "e", "f"};
            vector<Dependency> dependencies{
                    {"a", "d"},
                    {"f", "b"},
                    {"b", "d"},
                    {"f", "a"},
                    {"d", "c"}
            };

            auto order = findBuildOrder(projects, dependencies);
            REQUIRE(order.empty() == false);
            printf("[04-07.Solution1] Project order exists:\n");
            if (order.empty()) {
                printf("No order exists!");
            } else {
                for (auto each : order) {
                    printf("%s ", each.c_str());
                }
                printf("\n");
            }
        }

        SECTION("Project order does not exist") {
            vector<string> projects{"a", "b", "c", "d", "e", "f"};
            vector<Dependency> dependencies{
                    {"a", "d"},
                    {"f", "b"},
                    {"b", "d"},
                    {"f", "a"},
                    {"d", "c"},
                    {"c", "f"}
            };

            auto order = findBuildOrder(projects, dependencies);
            REQUIRE(order.empty());
            printf("[04-07.Solution1] Project order does not exist:\n");
            if (order.empty()) {
                printf("No order exists!");
            } else {
                for (auto each : order) {
                    printf("%s ", each.c_str());
                }
                printf("\n");
            }
        }
    }

    SECTION("Solution2") {
        using namespace solution2;

        SECTION("Project order exists") {
            vector<string> projects{"a", "b", "c", "d", "e", "f"};
            vector<Dependency> dependencies{
                    {"a", "d"},
                    {"f", "b"},
                    {"b", "d"},
                    {"f", "a"},
                    {"d", "c"}
            };

            auto order = findBuildOrder(projects, dependencies);
            REQUIRE(order.empty() == false);
            printf("[04-07.Solution2] Project order exists:\n");
            if (order.empty()) {
                printf("No order exists!");
            } else {
                for (auto each : order) {
                    printf("%s ", each.c_str());
                }
                printf("\n");
            }
        }

        SECTION("Project order does not exist") {
            vector<string> projects{"a", "b", "c", "d", "e", "f"};
            vector<Dependency> dependencies{
                    {"a", "d"},
                    {"f", "b"},
                    {"b", "d"},
                    {"f", "a"},
                    {"d", "c"},
                    {"c", "f"}
            };

            auto order = findBuildOrder(projects, dependencies);
            REQUIRE(order.empty());
            printf("[04-07.Solution2] Project order does not exist:\n");
            if (order.empty()) {
                printf("No order exists!");
            } else {
                for (auto each : order) {
                    printf("%s ", each.c_str());
                }
                printf("\n");
            }
        }
    }

    SECTION("Solution3") {
        using namespace solution3;

        SECTION("Project order exists") {
            vector<string> projects{"a", "b", "c", "d", "e", "f"};
            vector<Dependency> dependencies{
                    {"a", "d"},
                    {"f", "b"},
                    {"b", "d"},
                    {"f", "a"},
                    {"d", "c"}
            };

            auto order = findBuildOrder(projects, dependencies);
            REQUIRE(order.empty() == false);
            printf("[04-07.Solution3] Project order exists:\n");
            if (order.empty()) {
                printf("No order exists!");
            } else {
                for (auto each : order) {
                    printf("%s ", each.c_str());
                }
                printf("\n");
            }
        }

        SECTION("Project order does not exist") {
            vector<string> projects{"a", "b", "c", "d", "e", "f"};
            vector<Dependency> dependencies{
                    {"a", "d"},
                    {"f", "b"},
                    {"b", "d"},
                    {"f", "a"},
                    {"d", "c"},
                    {"c", "f"}
            };

            auto order = findBuildOrder(projects, dependencies);
            REQUIRE(order.empty());
            printf("[04-07.Solution3] Project order does not exist:\n");
            if (order.empty()) {
                printf("No order exists!");
            } else {
                for (auto each : order) {
                    printf("%s ", each.c_str());
                }
                printf("\n");
            }
        }
    }
}

} // namespace ex_04_07