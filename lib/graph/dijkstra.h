class dijkstra
{
public:
    template <typename T>
    dijkstra(const graph<T>& g, int s)
    {
        dis.assign(g.size(), numeric_limits<T>::max()/2);
        dis[s] = 0;
        priority_queue<pair<T,int>, vector<pair<T,int>>, greater<>> pq;
        pq.emplace(0, s);
        while(!pq.empty())
        {
            auto [d,u] = pq.top();
            pq.pop();
            if(dis[u]<d) continue;
            g.for_each(u, [&](const auto& e)
            {
                if(dis[e.to]>dis[u]+e.cost)
                {
                    dis[e.to] = dis[u]+e.cost;
                    pq.emplace(dis[e.to], e.to);
                }
            });
        }
    }
    auto operator[](int u) const { return dis[u]; }
private:
    vector<int> dis;
};
