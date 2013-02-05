<p>
    Welcome back, <strong><?=$username?>!</strong> Your current deposit is <strong>$<?=number_format($cash, 2)?></strong>
</p>
<table class="table table-hover">
    <thead>
    <!--
        <tr>
            <th rowspan = 2>Symbol</th>
            <th rowspan = 2>Name</th>
            <th rowspan = 2>Shares</th>
            <th rowspan = 1 colspan = 2>Price</th>
            <th rowspan = 1 colspan = 2>Total</th>
            <th rowspan = 2>Total gains / losses</th>
        </tr>
        <tr>
            <th rowspan = 1>Bought</th>
            <th rowspan = 1>Current</th>
            <th rowspan = 1>Bought</th>
            <th rowspan = 1>Current</th>
        </tr>
    -->
        <tr>
            <th>Symbol</th>
            <th>Name</th>
            <th>Shares</th>
            <th>Price Bought</th>
            <th>Price Current</th>
            <th>Total Bought</th>
            <th>Total Current</th>
            <th>Total gains / losses</th>
        </tr>
    </thead>
    <tbody>
        <?php foreach($shares as $share): ?>
            <tr>
                <td><?= $share["symbol"] ?></td>
                <td><?= $share["name"] ?></td>
                <td><?= $share["shares"] ?></td>
                <td><?= number_format($share["price_bought"], 2) ?></td>
                <td><?= number_format($share["price_cur"], 2) ?></td>
                <td><?= number_format($share["total_bought"], 2) ?></td>
                <td><?= number_format($share["total_cur"], 2) ?></td>
                <td><?= number_format($share["profit"], 2) ?></td>
            </tr>
        <? endforeach ?>
    </tbody>
</table>
