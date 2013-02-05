<?php

    // configuration
    require("../includes/config.php"); 

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // Validate the name
        if (empty($_POST["code"]))
        {
            apologize("Please enter the stock symbol.");
        }
        // Validate the stock amount
        if (empty($_POST["shares"]) || !is_numeric($_POST["shares"]) || !preg_match("/^\d+$/", $_POST["shares"]))
        {
            apologize("Please enter the correct amount of shares!");
        }
        
        // Query the Yahoo
        $stock = lookup($_POST["code"]);
        
        // Check if we returned nothing
        if ($stock === false)
        {
            apologize("Entered stock symbol was invalid.");
        }
        else
        {
            $value = $stock["price"] * $_POST["shares"];
            
            // Check the amount of cash
            if ($_SESSION["cash"] < $value)
            {
                apologize("You don't have sufficient amount of deposited money.");
            }
            else
            {
                // Insert the bought stock into database
                $query = query("INSERT INTO shares(user_id, symbol, shares, price) VALUES (?, ?, ?, ?)
                    ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares), price = VALUES(price)"
                    ,$_SESSION["id"], strtoupper($stock["symbol"]), $_POST["shares"], $stock["price"]);
                if ($query === false)
                {
                    apologize("Error while buying shares.");
                }
                
                // Update the user's cash
                $query = query("UPDATE users SET cash = cash - ? where id = ?", $value, $_SESSION["id"]);
                if ($query === false)
                {
                    apologize("Error while buying shares.");
                }
              
                $_SESSION["cash"] -= $value;
                
                // Log the history
                $query = query("INSERT INTO history(user_id, type, symbol, shares, price, date) VALUES (?, ?, ?, ?, ?, Now())"
                    ,$_SESSION["id"], 1, strtoupper($stock["symbol"]), $_POST["shares"], $stock["price"]);
                
                // Redirect to home
                redirect("/");
            }
        }
    }
    else
    {
        // else render form
        render("buy_form.php", ["title" => "Buy"]);
    }
?>
