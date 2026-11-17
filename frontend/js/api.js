// API Service Layer
const API_BASE_URL = 'http://localhost:5000/api';

class APIService {
    // Network API
    async getRouters() {
        try {
            const response = await fetch(`${API_BASE_URL}/routers`);
            return await response.json();
        } catch (error) {
            console.error('Error fetching routers:', error);
            return { success: false, error: error.message };
        }
    }

    async addRouter(routerData) {
        try {
            const response = await fetch(`${API_BASE_URL}/routers`, {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify(routerData)
            });
            return await response.json();
        } catch (error) {
            console.error('Error adding router:', error);
            return { success: false, error: error.message };
        }
    }

    async deleteRouter(routerId) {
        try {
            const response = await fetch(`${API_BASE_URL}/routers/${routerId}`, {
                method: 'DELETE'
            });
            return await response.json();
        } catch (error) {
            console.error('Error deleting router:', error);
            return { success: false, error: error.message };
        }
    }

    async getLinks() {
        try {
            const response = await fetch(`${API_BASE_URL}/links`);
            return await response.json();
        } catch (error) {
            console.error('Error fetching links:', error);
            return { success: false, error: error.message };
        }
    }

    async addLink(linkData) {
        try {
            const response = await fetch(`${API_BASE_URL}/links`, {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify(linkData)
            });
            return await response.json();
        } catch (error) {
            console.error('Error adding link:', error);
            return { success: false, error: error.message };
        }
    }

    async deleteLink(linkId) {
        try {
            const response = await fetch(`${API_BASE_URL}/links/${linkId}`, {
                method: 'DELETE'
            });
            return await response.json();
        } catch (error) {
            console.error('Error deleting link:', error);
            return { success: false, error: error.message };
        }
    }

    async getGraph() {
        try {
            const response = await fetch(`${API_BASE_URL}/network/graph`);
            return await response.json();
        } catch (error) {
            console.error('Error fetching graph:', error);
            return { success: false, error: error.message };
        }
    }

    // Routing API
    async runBFS(source, destination) {
        try {
            const response = await fetch(`${API_BASE_URL}/routing/bfs`, {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({ source, destination })
            });
            return await response.json();
        } catch (error) {
            console.error('Error running BFS:', error);
            return { success: false, error: error.message };
        }
    }

    async runDFS(source, destination) {
        try {
            const response = await fetch(`${API_BASE_URL}/routing/dfs`, {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({ source, destination })
            });
            return await response.json();
        } catch (error) {
            console.error('Error running DFS:', error);
            return { success: false, error: error.message };
        }
    }

    async runDijkstra(source, destination) {
        try {
            const response = await fetch(`${API_BASE_URL}/routing/dijkstra`, {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({ source, destination })
            });
            return await response.json();
        } catch (error) {
            console.error('Error running Dijkstra:', error);
            return { success: false, error: error.message };
        }
    }

    // Packets API
    async getPackets() {
        try {
            const response = await fetch(`${API_BASE_URL}/packets`);
            return await response.json();
        } catch (error) {
            console.error('Error fetching packets:', error);
            return { success: false, error: error.message };
        }
    }

    async addPacket(packetData) {
        try {
            const response = await fetch(`${API_BASE_URL}/packets`, {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify(packetData)
            });
            return await response.json();
        } catch (error) {
            console.error('Error adding packet:', error);
            return { success: false, error: error.message };
        }
    }

    async processPacket() {
        try {
            const response = await fetch(`${API_BASE_URL}/packets/process`, {
                method: 'POST'
            });
            return await response.json();
        } catch (error) {
            console.error('Error processing packet:', error);
            return { success: false, error: error.message };
        }
    }

    // Sorting API
    async runSort(algorithm, array) {
        try {
            const response = await fetch(`${API_BASE_URL}/sorting/run`, {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({ algorithm, array })
            });
            return await response.json();
        } catch (error) {
            console.error('Error running sort:', error);
            return { success: false, error: error.message };
        }
    }

    // Search API
    async runSearch(algorithm, array, element) {
        try {
            const response = await fetch(`${API_BASE_URL}/search/run`, {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({ algorithm, array, element })
            });
            return await response.json();
        } catch (error) {
            console.error('Error running search:', error);
            return { success: false, error: error.message };
        }
    }

    // Tree API
    async getTree() {
        try {
            const response = await fetch(`${API_BASE_URL}/trees/get`);
            return await response.json();
        } catch (error) {
            console.error('Error fetching tree:', error);
            return { success: false, error: error.message };
        }
    }

    async runTreeOperation(operation, value) {
        try {
            const response = await fetch(`${API_BASE_URL}/trees/operation`, {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({ operation, value })
            });
            return await response.json();
        } catch (error) {
            console.error('Error running tree operation:', error);
            return { success: false, error: error.message };
        }
    }

    async runTreeTraversal(traversal) {
        try {
            const response = await fetch(`${API_BASE_URL}/trees/traversal`, {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({ traversal })
            });
            return await response.json();
        } catch (error) {
            console.error('Error running tree traversal:', error);
            return { success: false, error: error.message };
        }
    }

    // Dashboard API
    async getDashboardStats() {
        try {
            const response = await fetch(`${API_BASE_URL}/dashboard/stats`);
            return await response.json();
        } catch (error) {
            console.error('Error fetching dashboard stats:', error);
            return { success: false, error: error.message };
        }
    }

    async getActivityLog() {
        try {
            const response = await fetch(`${API_BASE_URL}/dashboard/activity`);
            return await response.json();
        } catch (error) {
            console.error('Error fetching activity log:', error);
            return { success: false, error: error.message };
        }
    }

    // Performance API
    async runBenchmark() {
        try {
            const response = await fetch(`${API_BASE_URL}/analysis/benchmark`, {
                method: 'POST'
            });
            return await response.json();
        } catch (error) {
            console.error('Error running benchmark:', error);
            return { success: false, error: error.message };
        }
    }

    // Reset Data
    async resetData() {
        try {
            const response = await fetch(`${API_BASE_URL}/reset`, {
                method: 'POST'
            });
            return await response.json();
        } catch (error) {
            console.error('Error resetting data:', error);
            return { success: false, error: error.message };
        }
    }
}

// Export API service
const api = new APIService();
