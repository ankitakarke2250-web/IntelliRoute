// Main Application JavaScript
document.addEventListener('DOMContentLoaded', function() {
    // Navigation
    const navItems = document.querySelectorAll('.nav-item');
    const pages = document.querySelectorAll('.page');
    const pageTitle = document.getElementById('page-title');

    navItems.forEach(item => {
        item.addEventListener('click', function(e) {
            e.preventDefault();
            const pageName = this.getAttribute('data-page');

            // Update active nav item
            navItems.forEach(nav => nav.classList.remove('active'));
            this.classList.add('active');

            // Show corresponding page
            pages.forEach(page => page.classList.add('hidden'));
            const targetPage = document.getElementById(`${pageName}-page`);
            if (targetPage) {
                targetPage.classList.remove('hidden');
                pageTitle.textContent = this.textContent.trim();

                // Load page-specific data
                loadPageData(pageName);
            }
        });
    });

    // Load page-specific data
    async function loadPageData(pageName) {
        switch(pageName) {
            case 'dashboard':
                await loadDashboard();
                break;
            case 'network':
                await loadNetworkData();
                break;
            case 'topology':
                await loadTopology();
                break;
            case 'routing':
                await loadRoutingData();
                break;
            case 'packets':
                await loadPacketData();
                break;
            case 'sorting':
                // Pre-load with sample data
                document.getElementById('sorting-input').value = '5, 3, 8, 1, 9, 2, 7, 4, 6';
                break;
            case 'trees':
                await renderModernBST();
                break;
            case 'analysis':
                break;
        }
    }

    // Dashboard
    async function loadDashboard() {
        const stats = await api.getDashboardStats();
        if (stats.success) {
            document.getElementById('stat-routers').textContent = stats.data.total_routers;
            document.getElementById('stat-active').textContent = stats.data.active_routers;
            document.getElementById('stat-connections').textContent = stats.data.total_connections;
            document.getElementById('stat-packets').textContent = stats.data.total_packets;
            document.getElementById('stat-pending').textContent = stats.data.pending_packets;
            document.getElementById('stat-processed').textContent = stats.data.processed_packets;
        }

        const activity = await api.getActivityLog();
        const activityLog = document.getElementById('activity-log');
        if (activity.success && activity.data.length > 0) {
            activityLog.innerHTML = activity.data.map(log =>
                `<p>${log.timestamp} - ${log.action} (${log.status})</p>`
            ).join('');
        } else {
            activityLog.innerHTML = '<p class="no-data">No recent activities</p>';
        }

        // Load topology preview
        const graph = await api.getGraph();
        if (graph.success && graph.data.elements.nodes.length > 0) {
            renderTopologyPreview(graph.data);
        }
    }

    function renderTopologyPreview(graphData) {
        const cy = cytoscape({
            container: document.getElementById('topology-preview'),
            elements: graphData.elements,
            style: [
                {
                    selector: 'node',
                    style: {
                        'background-color': '#2563eb',
                        'label': 'data(label)',
                        'color': '#fff',
                        'text-valign': 'center',
                        'text-halign': 'center',
                        'width': '40px',
                        'height': '40px',
                        'font-size': '10px'
                    }
                },
                {
                    selector: 'edge',
                    style: {
                        'width': 2,
                        'line-color': '#475569',
                        'target-arrow-color': '#475569',
                        'target-arrow-shape': 'triangle',
                        'curve-style': 'bezier',
                        'label': 'data(label)',
                        'color': '#ffffff',
                        'text-background-color': '#1e293b',
                        'text-background-opacity': 0.8,
                        'text-background-padding': '2px',
                        'text-background-shape': 'roundrectangle',
                        'font-size': '9px',
                        'text-rotation': 'autorotate',
                        'text-margin-y': -8
                    }
                }
            ],
            layout: {
                name: 'cose',
                animate: false,
                animationDuration: 0
            },
            zoom: 0.8,
            pan: { x: 100, y: 100 }
        });
    }

    // Network Management
    async function loadNetworkData() {
        const routers = await api.getRouters();
        if (routers.success) {
            renderRoutersTable(routers.data);
            populateRouterSelects(routers.data);
        }

        const links = await api.getLinks();
        if (links.success) {
            renderLinksTable(links.data);
        }
    }

    function renderRoutersTable(routers) {
        const tbody = document.getElementById('routers-table-body');
        if (routers.length === 0) {
            tbody.innerHTML = '<tr><td colspan="6" class="no-data">No routers available</td></tr>';
            return;
        }

        tbody.innerHTML = routers.map(router => `
            <tr>
                <td>${router.id}</td>
                <td>${router.name}</td>
                <td>${router.ip}</td>
                <td><span class="status-badge ${router.status}">${router.status}</span></td>
                <td>${router.connections || 0}</td>
                <td>
                    <button class="btn btn-sm btn-danger" onclick="deleteRouter(${router.id})">
                        <i class="fas fa-trash"></i>
                    </button>
                </td>
            </tr>
        `).join('');
    }

    function renderLinksTable(links) {
        const tbody = document.getElementById('connections-table-body');
        if (links.length === 0) {
            tbody.innerHTML = '<tr><td colspan="5" class="no-data">No connections available</td></tr>';
            return;
        }

        tbody.innerHTML = links.map(link => `
            <tr>
                <td>${link.id}</td>
                <td>${link.source}</td>
                <td>${link.destination}</td>
                <td>${link.cost}</td>
                <td>
                    <button class="btn btn-sm btn-danger" onclick="deleteLink(${link.id})">
                        <i class="fas fa-trash"></i>
                    </button>
                </td>
            </tr>
        `).join('');
    }

    function populateRouterSelects(routers) {
        const selects = ['source-router', 'dest-router', 'routing-source', 'routing-destination', 'packet-source', 'packet-destination'];
        selects.forEach(selectId => {
            const select = document.getElementById(selectId);
            if (select) {
                select.innerHTML = routers.map(r => `<option value="${r.id}">${r.name} (${r.id})</option>`).join('');
            }
        });
    }

    // Router Form
    document.getElementById('add-router-btn').addEventListener('click', function() {
        document.getElementById('router-form').classList.remove('hidden');
    });

    document.getElementById('cancel-router').addEventListener('click', function() {
        document.getElementById('router-form').classList.add('hidden');
        document.getElementById('router-add-form').reset();
    });

    document.getElementById('router-add-form').addEventListener('submit', async function(e) {
        e.preventDefault();
        const routerData = {
            name: document.getElementById('router-name').value,
            ip: document.getElementById('router-ip').value,
            status: document.getElementById('router-status').value
        };

        const result = await api.addRouter(routerData);
        if (result.success) {
            showToast('Router added successfully', 'success');
            document.getElementById('router-form').classList.add('hidden');
            document.getElementById('router-add-form').reset();
            await loadNetworkData();
        } else {
            showToast('Error adding router: ' + result.error, 'error');
        }
    });

    // Connection Form
    document.getElementById('add-connection-btn').addEventListener('click', function() {
        document.getElementById('connection-form').classList.remove('hidden');
    });

    document.getElementById('cancel-connection').addEventListener('click', function() {
        document.getElementById('connection-form').classList.add('hidden');
        document.getElementById('connection-add-form').reset();
    });

    document.getElementById('connection-add-form').addEventListener('submit', async function(e) {
        e.preventDefault();
        const linkData = {
            source: document.getElementById('source-router').value,
            destination: document.getElementById('dest-router').value,
            cost: parseInt(document.getElementById('connection-cost').value)
        };

        const result = await api.addLink(linkData);
        if (result.success) {
            showToast('Connection added successfully', 'success');
            document.getElementById('connection-form').classList.add('hidden');
            document.getElementById('connection-add-form').reset();
            await loadNetworkData();
        } else {
            showToast('Error adding connection: ' + result.error, 'error');
        }
    });

    // Topology
    async function loadTopology() {
        const graph = await api.getGraph();
        if (graph.success) {
            renderTopology(graph.data);
        }
    }

    function renderTopology(graphData) {
        const cy = cytoscape({
            container: document.getElementById('cy'),
            elements: graphData.elements,
            style: [
                {
                    selector: 'node',
                    style: {
                        'background-color': '#2563eb',
                        'label': 'data(label)',
                        'color': '#fff',
                        'text-valign': 'center',
                        'text-halign': 'center',
                        'width': '60px',
                        'height': '60px',
                        'font-size': '14px'
                    }
                },
                {
                    selector: 'edge',
                    style: {
                        'width': 3,
                        'line-color': '#475569',
                        'target-arrow-color': '#475569',
                        'target-arrow-shape': 'triangle',
                        'curve-style': 'bezier',
                        'label': 'data(label)',
                        'color': '#ffffff',
                        'text-background-color': '#1e293b',
                        'text-background-opacity': 0.8,
                        'text-background-padding': '3px',
                        'text-background-shape': 'roundrectangle',
                        'font-size': '12px',
                        'text-rotation': 'autorotate',
                        'text-margin-y': -10
                    }
                }
            ],
            layout: {
                name: 'cose',
                animate: true,
                animationDuration: 500
            }
        });
    }

    document.getElementById('refresh-topology').addEventListener('click', async function() {
        await loadTopology();
        showToast('Topology refreshed', 'success');
    });

    // Routing
    async function loadRoutingData() {
        const routers = await api.getRouters();
        if (routers.success) {
            populateRouterSelects(routers.data);
        }
    }

    document.getElementById('run-routing').addEventListener('click', async function() {
        const source = document.getElementById('routing-source').value;
        const destination = document.getElementById('routing-destination').value;
        const algorithm = document.getElementById('routing-algorithm').value;

        let result;
        switch(algorithm) {
            case 'bfs':
                result = await api.runBFS(source, destination);
                break;
            case 'dfs':
                result = await api.runDFS(source, destination);
                break;
            case 'dijkstra':
                result = await api.runDijkstra(source, destination);
                break;
        }

        if (result.success) {
            document.getElementById('routing-results').classList.remove('hidden');
            document.getElementById('traversal-order').textContent = result.data.traversal.join(' → ');
            document.getElementById('calculated-route').textContent = result.data.route.join(' → ');
            document.getElementById('total-cost').textContent = result.data.cost;
            showToast(`${algorithm.toUpperCase()} completed successfully`, 'success');
        } else {
            showToast('Error running routing: ' + result.error, 'error');
        }
    });

    // Packets
    async function loadPacketData() {
        const routers = await api.getRouters();
        if (routers.success) {
            populateRouterSelects(routers.data);
        }

        const packets = await api.getPackets();
        if (packets.success) {
            renderPacketsTable(packets.data);
        }
    }

    function renderPacketsTable(packets) {
        const tbody = document.getElementById('packets-table-body');
        if (packets.length === 0) {
            tbody.innerHTML = '<tr><td colspan="6" class="no-data">No packets available</td></tr>';
            return;
        }

        tbody.innerHTML = packets.map(packet => `
            <tr>
                <td>${packet.id}</td>
                <td>${packet.source}</td>
                <td>${packet.destination}</td>
                <td>${packet.size} KB</td>
                <td>${packet.priority}</td>
                <td><span class="status-badge ${packet.status}">${packet.status}</span></td>
            </tr>
        `).join('');
    }

    document.getElementById('generate-packet-btn').addEventListener('click', function() {
        document.getElementById('packet-form').classList.remove('hidden');
    });

    document.getElementById('cancel-packet').addEventListener('click', function() {
        document.getElementById('packet-form').classList.add('hidden');
        document.getElementById('packet-add-form').reset();
    });

    document.getElementById('packet-add-form').addEventListener('submit', async function(e) {
        e.preventDefault();
        const packetData = {
            source: document.getElementById('packet-source').value,
            destination: document.getElementById('packet-destination').value,
            size: parseInt(document.getElementById('packet-size').value),
            priority: document.getElementById('packet-priority').value
        };

        const result = await api.addPacket(packetData);
        if (result.success) {
            showToast('Packet generated successfully', 'success');
            document.getElementById('packet-form').classList.add('hidden');
            document.getElementById('packet-add-form').reset();
            await loadPacketData();
        } else {
            showToast('Error generating packet: ' + result.error, 'error');
        }
    });

    document.getElementById('process-packet').addEventListener('click', async function() {
        const result = await api.processPacket();
        if (result.success) {
            showToast('Packet processed successfully', 'success');
            await loadPacketData();
        } else {
            showToast('Error processing packet: ' + result.error, 'error');
        }
    });

    // Sorting
    document.getElementById('generate-random').addEventListener('click', function() {
        const randomArray = Array.from({length: 10}, () => Math.floor(Math.random() * 100) + 1);
        document.getElementById('sorting-input').value = randomArray.join(', ');
    });

    document.getElementById('run-sorting').addEventListener('click', async function() {
        const input = document.getElementById('sorting-input').value;
        const algorithm = document.getElementById('sorting-algorithm').value;
        const array = input.split(',').map(n => parseInt(n.trim())).filter(n => !isNaN(n));

        if (array.length === 0) {
            showToast('Please enter valid numbers', 'error');
            return;
        }

        const result = await api.runSort(algorithm, array);
        if (result.success) {
            document.getElementById('sorting-results').classList.remove('hidden');
            document.getElementById('original-array').textContent = result.data.original.join(', ');
            document.getElementById('sorted-array').textContent = result.data.sorted.join(', ');
            document.getElementById('sorting-comparisons').textContent = result.data.comparisons;
            document.getElementById('sorting-swaps').textContent = result.data.swaps;
            document.getElementById('sorting-time').textContent = result.data.time + ' ms';
            showToast('Sorting completed', 'success');
            
            // Refresh activity log
            const activity = await api.getActivityLog();
            if (activity.success && activity.data.length > 0) {
                const activityLog = document.getElementById('activity-log');
                activityLog.innerHTML = activity.data.map(log =>
                    `<p>${log.timestamp} - ${log.action} (${log.status})</p>`
                ).join('');
            }
        } else {
            showToast('Error running sort: ' + result.error, 'error');
        }
    });

    // Searching
    document.getElementById('run-search').addEventListener('click', async function() {
        const element = parseInt(document.getElementById('search-input').value);
        const algorithm = document.getElementById('search-algorithm').value;
        const input = document.getElementById('sorting-input').value;
        const array = input.split(',').map(n => parseInt(n.trim())).filter(n => !isNaN(n));

        if (isNaN(element)) {
            showToast('Please enter a valid number to search', 'error');
            return;
        }

        if (array.length === 0) {
            showToast('Please enter numbers to search in', 'error');
            return;
        }

        const result = await api.runSearch(algorithm, array, element);
        if (result.success) {
            document.getElementById('search-results').classList.remove('hidden');
            document.getElementById('search-result').textContent = result.data.found ? 'Found' : 'Not Found';
            document.getElementById('search-position').textContent = result.data.position !== -1 ? result.data.position : 'N/A';
            document.getElementById('search-comparisons').textContent = result.data.comparisons;
            showToast('Search completed', 'success');
        } else {
            showToast('Error running search: ' + result.error, 'error');
        }
    });

    // Tree Operations
    document.getElementById('run-tree-operation').addEventListener('click', async function() {
        const operation = document.getElementById('tree-operation').value;
        const value = parseInt(document.getElementById('tree-value').value);

        if (isNaN(value)) {
            showToast('Please enter a valid number', 'error');
            return;
        }

        const result = await api.runTreeOperation(operation, value);
        if (result.success) {
            document.getElementById('tree-results').classList.remove('hidden');
            document.getElementById('tree-height').textContent = result.data.height;
            document.getElementById('leaf-nodes').textContent = result.data.leaf_nodes;

            // Show specific message based on operation
            if (operation === 'insert') {
                showToast(`Node ${value} inserted successfully`, 'success');
            } else if (operation === 'delete') {
                showToast(`Node ${value} deleted successfully`, 'success');
            } else if (operation === 'search') {
                if (result.data.found) {
                    showToast(`Node ${value} found in tree`, 'success');
                } else {
                    showToast(`Node ${value} not found in tree`, 'error');
                }
            }

            // Refresh tree visualization with real data
            await renderModernBST();
        } else {
            showToast('Error running tree operation: ' + result.error, 'error');
        }
    });

    // Tree Traversals
    document.querySelectorAll('[data-traversal]').forEach(btn => {
        btn.addEventListener('click', async function() {
            const traversal = this.getAttribute('data-traversal');
            const result = await api.runTreeTraversal(traversal);
            if (result.success) {
                document.getElementById('tree-results').classList.remove('hidden');
                document.getElementById('traversal-result').textContent = result.data.result.join(' → ');
                document.getElementById('tree-height').textContent = result.data.height || 'N/A';
                document.getElementById('leaf-nodes').textContent = result.data.leaf_nodes || 'N/A';
                showToast(`${traversal} traversal completed`, 'success');
            } else {
                showToast('Error running traversal: ' + result.error, 'error');
            }
        });
    });

    // Modern BST Visualization
    async function renderModernBST() {
        const container = document.getElementById('tree-container');
        if (!container) {
            console.error('Tree container not found');
            return;
        }

        console.log('Rendering tree visualization...');

        // Get current tree state
        const treeData = await api.getTree();
        console.log('Tree data:', treeData);

        if (!treeData.success || !treeData.data.nodes || treeData.data.nodes.length === 0) {
            container.innerHTML = `
                <div class="empty-tree-state">
                    <div class="empty-icon"><i class="fas fa-tree"></i></div>
                    <p>Tree is empty. Insert nodes to build your BST.</p>
                </div>
            `;
            return;
        }

        const nodes = treeData.data.nodes;
        console.log('Nodes:', nodes);

        // Build BST structure from nodes
        const bstStructure = buildBSTStructure(nodes);
        console.log('BST structure:', bstStructure);

        // Render with modern glowing UI using HTML/CSS instead of SVG
        container.innerHTML = `
            <div class="modern-bst-container" id="bst-container">
                <div class="bst-html-container" id="bst-content">
                    ${renderBSTHTML(bstStructure)}
                </div>
                <div class="bst-info">
                    <div class="info-badge">
                        <i class="fas fa-database"></i>
                        <span>Nodes: ${nodes.length}</span>
                    </div>
                    <div class="info-badge">
                        <i class="fas fa-layer-group"></i>
                        <span>Height: ${treeData.data.height}</span>
                    </div>
                    <div class="info-badge">
                        <i class="fas fa-leaf"></i>
                        <span>Leaves: ${treeData.data.leaf_nodes}</span>
                    </div>
                </div>
            </div>
        `;
        console.log('Tree visualization rendered');

        // Add pan/zoom functionality
        initTreePanZoom();
    }

    function initTreePanZoom() {
        const container = document.getElementById('bst-container');
        const content = document.getElementById('bst-content');
        if (!container || !content) return;

        let isDragging = false;
        let startX, startY, scrollLeft, scrollTop;
        let scale = 1;

        container.addEventListener('mousedown', (e) => {
            isDragging = true;
            startX = e.pageX - container.offsetLeft;
            startY = e.pageY - container.offsetTop;
            scrollLeft = container.scrollLeft;
            scrollTop = container.scrollTop;
            container.style.cursor = 'grabbing';
        });

        container.addEventListener('mouseleave', () => {
            isDragging = false;
            container.style.cursor = 'grab';
        });

        container.addEventListener('mouseup', () => {
            isDragging = false;
            container.style.cursor = 'grab';
        });

        container.addEventListener('mousemove', (e) => {
            if (!isDragging) return;
            e.preventDefault();
            const x = e.pageX - container.offsetLeft;
            const y = e.pageY - container.offsetTop;
            const walkX = (x - startX) * 1;
            const walkY = (y - startY) * 1;
            container.scrollLeft = scrollLeft - walkX;
            container.scrollTop = scrollTop - walkY;
        });

        // Zoom with mouse wheel
        container.addEventListener('wheel', (e) => {
            e.preventDefault();
            const delta = e.deltaY > 0 ? 0.9 : 1.1;
            scale *= delta;
            scale = Math.min(Math.max(0.5, scale), 2);
            content.style.transform = `scale(${scale})`;
        });
    }

    function buildBSTStructure(nodes) {
        // Simplified BST construction (sorted array to BST)
        const sorted = [...nodes].sort((a, b) => a - b);
        const buildBalanced = (arr, start, end) => {
            if (start > end) return null;
            const mid = Math.floor((start + end) / 2);
            return {
                value: arr[mid],
                left: buildBalanced(arr, start, mid - 1),
                right: buildBalanced(arr, mid + 1, end)
            };
        };
        return buildBalanced(sorted, 0, sorted.length - 1);
    }

    function renderBSTHTML(node) {
        if (!node) {
            return `<div class="bst-null-node">NULL</div>`;
        }

        const leftHTML = renderBSTHTML(node.left);
        const rightHTML = renderBSTHTML(node.right);

        const hasChildren = node.left || node.right;

        return `
            <div class="bst-node-wrapper">
                <div class="bst-node">${node.value}</div>
                ${hasChildren ? `
                    <div class="bst-children">
                        <div class="bst-connector-horizontal"></div>
                        ${node.left ? `
                            <div class="bst-child bst-left">
                                <div class="bst-connector"></div>
                                ${leftHTML}
                            </div>
                        ` : `
                            <div class="bst-child bst-left">
                                <div class="bst-connector"></div>
                                <div class="bst-null-node">NULL</div>
                            </div>
                        `}
                        ${node.right ? `
                            <div class="bst-child bst-right">
                                <div class="bst-connector"></div>
                                ${rightHTML}
                            </div>
                        ` : `
                            <div class="bst-child bst-right">
                                <div class="bst-connector"></div>
                                <div class="bst-null-node">NULL</div>
                            </div>
                        `}
                    </div>
                ` : `
                    <div class="bst-children">
                        <div class="bst-connector-horizontal"></div>
                        <div class="bst-child bst-left">
                            <div class="bst-connector"></div>
                            <div class="bst-null-node">NULL</div>
                        </div>
                        <div class="bst-child bst-right">
                            <div class="bst-connector"></div>
                            <div class="bst-null-node">NULL</div>
                        </div>
                    </div>
                `}
            </div>
        `;
    }

    // Load tree page
    navItems.forEach(item => {
        if (item.getAttribute('data-page') === 'trees') {
            item.addEventListener('click', function() {
                setTimeout(renderModernBST, 100);
            });
        }
    });

    // Benchmark
    document.getElementById('run-benchmark').addEventListener('click', async function() {
        const result = await api.runBenchmark();
        if (result.success) {
            document.getElementById('benchmark-results').classList.remove('hidden');
            renderBenchmarkCharts(result.data);
            showToast('Benchmark completed', 'success');
        } else {
            showToast('Error running benchmark: ' + result.error, 'error');
        }
    });

    function renderBenchmarkCharts(data) {
        // Sorting chart
        const sortingCtx = document.getElementById('sorting-chart').getContext('2d');
        new Chart(sortingCtx, {
            type: 'bar',
            data: {
                labels: data.sorting.map(s => s.algorithm),
                datasets: [{
                    label: 'Execution Time (ms)',
                    data: data.sorting.map(s => s.time),
                    backgroundColor: '#2563eb'
                }]
            },
            options: {
                responsive: true,
                plugins: {
                    legend: { labels: { color: '#f1f5f9' } },
                    title: {
                        display: true,
                        text: data.note || 'Sorting Algorithm Performance',
                        color: '#f1f5f9'
                    }
                },
                scales: {
                    y: { ticks: { color: '#94a3b8' }, grid: { color: '#334155' } },
                    x: { ticks: { color: '#94a3b8' }, grid: { color: '#334155' } }
                }
            }
        });

        // Search chart
        const searchCtx = document.getElementById('search-chart').getContext('2d');
        new Chart(searchCtx, {
            type: 'bar',
            data: {
                labels: data.search.map(s => s.algorithm),
                datasets: [{
                    label: 'Comparisons',
                    data: data.search.map(s => s.comparisons),
                    backgroundColor: '#10b981'
                }]
            },
            options: {
                responsive: true,
                plugins: {
                    legend: { labels: { color: '#f1f5f9' } },
                    title: {
                        display: true,
                        text: 'Search Algorithm Performance',
                        color: '#f1f5f9'
                    }
                },
                scales: {
                    y: { ticks: { color: '#94a3b8' }, grid: { color: '#334155' } },
                    x: { ticks: { color: '#94a3b8' }, grid: { color: '#334155' } }
                }
            }
        });
    }

    // Reset Data
    document.getElementById('reset-data').addEventListener('click', async function() {
        if (confirm('Are you sure you want to reset all data? This cannot be undone.')) {
            const result = await api.resetData();
            if (result.success) {
                showToast('Data reset successfully', 'success');
                await loadDashboard();
            } else {
                showToast('Error resetting data: ' + result.error, 'error');
            }
        }
    });

    // Toast Notifications
    function showToast(message, type = 'success') {
        const container = document.getElementById('toast-container');
        const toast = document.createElement('div');
        toast.className = `toast ${type}`;

        const icon = type === 'success' ? 'fa-check-circle' :
                    type === 'error' ? 'fa-exclamation-circle' :
                    'fa-exclamation-triangle';

        toast.innerHTML = `<i class="fas ${icon}"></i><span>${message}</span>`;
        container.appendChild(toast);

        setTimeout(() => {
            toast.remove();
        }, 3000);
    }

    // Make functions global for onclick handlers
    window.deleteRouter = async function(id) {
        if (confirm('Are you sure you want to delete this router?')) {
            const result = await api.deleteRouter(id);
            if (result.success) {
                showToast('Router deleted successfully', 'success');
                await loadNetworkData();
            } else {
                showToast('Error deleting router: ' + result.error, 'error');
            }
        }
    };

    window.deleteLink = async function(id) {
        if (confirm('Are you sure you want to delete this connection?')) {
            const result = await api.deleteLink(id);
            if (result.success) {
                showToast('Connection deleted successfully', 'success');
                await loadNetworkData();
            } else {
                showToast('Error deleting connection: ' + result.error, 'error');
            }
        }
    };

    // Load dashboard on initial load
    loadDashboard();
});
