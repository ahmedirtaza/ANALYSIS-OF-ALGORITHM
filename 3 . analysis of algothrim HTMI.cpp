<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Stock Market System</title>
    <style>
        body { font-family: Arial, sans-serif; }
        .menu { margin-bottom: 20px; }
        .form-group { margin-bottom: 10px; }
        .stocks-list { margin-top: 20px; }
        .btn { padding: 8px 15px; margin-right: 10px; }
        input[type="number"] { width: 120px; }
        input[type="text"] { width: 200px; }
        label { display: inline-block; width: 70px; }
    </style>
</head>
<body>
    <h1>Stock Market System</h1>
    <div class="menu">
        <button class="btn" onclick="showSection('add')">Add Stocks</button>
        <button class="btn" onclick="displayStocks()">Display Stocks</button>
        <button class="btn" onclick="showSection('sort')">Sort Stocks</button>
    </div>

    <div id="add-section" style="display:none;">
        <h2>Add Stock</h2>
        <div class="form-group">
            <label>Symbol:</label>
            <input type="text" id="symbol" maxlength="10">
        </div>
        <div class="form-group">
            <label>Name:</label>
            <input type="text" id="name">
        </div>
        <div class="form-group">
            <label>Price:</label>
            <input type="number" id="price" step="0.01">
        </div>
        <button onclick="addStock()">Add Stock</button>
        <span id="add-msg"></span>
    </div>

    <div id="sort-section" style="display:none;">
        <h2>Sort Stocks</h2>
        <label for="sort-criteria">Sort by:</label>
        <select id="sort-criteria">
            <option value="1">Price</option>
            <option value="2">Symbol</option>
            <option value="3">Name</option>
        </select>
        <button onclick="sortStocks()">Sort</button>
        <span id="sort-msg"></span>
    </div>

    <div class="stocks-list" id="stocks-list">
        <!-- Display stocks here -->
    </div>

    <script>
    let stocks = [];

    function showSection(section) {
        document.getElementById('add-section').style.display = section === 'add' ? 'block' : 'none';
        document.getElementById('sort-section').style.display = section === 'sort' ? 'block' : 'none';
        document.getElementById('add-msg').textContent = '';
        document.getElementById('sort-msg').textContent = '';
    }

    function addStock() {
        let symbol = document.getElementById('symbol').value.trim();
        let name = document.getElementById('name').value.trim();
        let price = parseFloat(document.getElementById('price').value);

        if (!symbol || !name || isNaN(price)) {
            document.getElementById('add-msg').textContent = "Please enter all fields!";
            return;
        }
        stocks.push({ symbol, name, price });
        document.getElementById('add-msg').textContent = "Stock added!";
        // Clear inputs
        document.getElementById('symbol').value = '';
        document.getElementById('name').value = '';
        document.getElementById('price').value = '';
        displayStocks();
    }

    function displayStocks() {
        let out = "";
        if (stocks.length === 0) {
            out = "<p>No stocks in the system.</p>";
        } else {
            out = `<table border="1" cellpadding="5"><tr>
                       <th>Symbol</th><th>Name</th><th>Price ($)</th></tr>`;
            for (const s of stocks) {
                out += `<tr>
                        <td>${s.symbol}</td>
                        <td>${s.name}</td>
                        <td>${s.price.toFixed(2)}</td>
                        </tr>`;
            }
            out += "</table>";
        }
        document.getElementById('stocks-list').innerHTML = out;
        showSection('');
    }

    function mergeSort(arr, sortBy) {
        if (arr.length < 2) return arr.slice();
        let mid = Math.floor(arr.length / 2);
        let left = mergeSort(arr.slice(0, mid), sortBy);
        let right = mergeSort(arr.slice(mid), sortBy);
        return merge(left, right, sortBy);
    }

    function merge(left, right, sortBy) {
        let result = [], i = 0, j = 0;
        while (i < left.length && j < right.length) {
            let takeLeft = false;
            if (sortBy == 1) // Price
                takeLeft = left[i].price <= right[j].price;
            else if (sortBy == 2) // Symbol
                takeLeft = left[i].symbol.localeCompare(right[j].symbol) <= 0;
            else // Name
                takeLeft = left[i].name.localeCompare(right[j].name) <= 0;
            if (takeLeft) result.push(left[i++]);
            else result.push(right[j++]);
        }
        while (i < left.length) result.push(left[i++]);
        while (j < right.length) result.push(right[j++]);
        return result;
    }

    function sortStocks() {
        if (stocks.length === 0) {
            document.getElementById('sort-msg').textContent = "No stocks to sort!";
            return;
        }
        let sortBy = parseInt(document.getElementById('sort-criteria').value);
        stocks = mergeSort(stocks, sortBy);
        document.getElementById('sort-msg').textContent = "Stocks sorted successfully.";
        displayStocks();
    }

    // Show stocks on initial load
    displayStocks();
    </script>
</body>
</html>
