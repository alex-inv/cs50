<form action="sell.php" method="post">
    <fieldset>
        <div class="control-group">
            <select name="code">
                <option value=''></option>
                <?
                    foreach($symbols as $symbol)
                    {
                        print("<option value='{$symbol["symbol"]}'>{$symbol["symbol"]}</option>\n");
                    }
                ?>
            </select>
        </div>
        <div class="control-group">
            <button type="submit" class="btn">Sell</button>
        </div>
    </fieldset>
</form>
