<?php
    // configuration
    require("../includes/config.php");
    
    // Query current users shares
    $rows = query("SELECT symbol, shares, price FROM shares WHERE user_id = ?", $_SESSION["id"]);
    
    // Construnct the view
    $shares = [];
    
    foreach($rows as $row)
    {
        // Query the Yahoo
        $stock = lookup($row["symbol"]);
        
        if ($stock !== false)
        {
            $shares[] = [
                "symbol"    => $row["symbol"]
                ,"name"     => $stock["name"]
                ,"shares"   => $row["shares"]
                ,"price_bought" => $row["price"]
                ,"price_cur"    => $stock["price"]
                ,"total_bought" => $row["shares"] * $row["price"]
                ,"total_cur"    => $row["shares"] * $stock["price"]
                ,"profit"   => $row["shares"] * $stock["price"] - $row["shares"] * $row["price"]               
            ];
        }
    }

    // render portfolio
    render("portfolio.php", ["title" => "Portfolio", "username" => $_SESSION["username"], "cash" => $_SESSION["cash"], "shares" => $shares]);

?>
