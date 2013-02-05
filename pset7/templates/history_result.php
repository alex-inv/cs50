<table class="table table-hover">
    <thead>
        <tr>
            <th>Action</th>
            <th>Symbol</th>
            <th>Shares</th>
            <th>Price</th>
            <th>Date</th>
        </tr>
    </thead>
    <tbody>
        <?php foreach($history as $record): ?>
            <tr>
                <td><?= $record["action"] ?></td>
                <td><?= $record["symbol"] ?></td>
                <td><?= $record["shares"] ?></td>
                <td><?= number_format($record["price"], 2) ?></td>
                <!--<td><?= $record["date"] ?></td>-->
                <td><?= date('Y-m-d H:i:s', strtotime($record["date"])) ?></td>
            </tr>
        <? endforeach ?>
    </tbody>
</table>
