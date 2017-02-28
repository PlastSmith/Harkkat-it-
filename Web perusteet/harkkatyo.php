<?php
require_once("connection.php");

require_once("config.php");

require_once("functions.php");

// Kysely, jolla saadaan pudotus valikoihin datan sisältämät paivamaarat.
$paivat = "SELECT pvm FROM sql_saa ORDER BY pvm ASC;";
$paivatTulokset = mysqli_query($conn, $paivat);
tarkistaYhteys($conn, $paivat);


// Tilastotaulukon tietojen sql kyselyt
if ($_SERVER["REQUEST_METHOD"] == "POST") {

    require_once("tilastonhakuRajoilla.php");
} else {
    // kysely tehdään ilman postin välittämiä tietoja
    require_once("tilastonhakuEiRajoja.php");
}

// Arvotaulukoiden tietojen sql kyselyt
if ($_SERVER["REQUEST_METHOD"] == "POST") {

    require_once("arvohakuRajoilla.php");

// Jos pvm haku tehty ja sarakkeiden mukaan järjestetty ainakin kerran(sarakejarjestykseen)    
// laitetaan sarakejärjestykseen joko ASC tai DESC sarakeotsikon parametrien perusteella
} else if ($_REQUEST["sarakejarjestykseen"] == "true") {

    require_once("arvohakuRajoillaSarake.php");

    // Haetaan kaikki tulokset kun ensimmäisen kerran tullaan sivulle.
} else {
    $arvoKysely = "SELECT * FROM sql_saa;";
    tarkistaYhteys($conn, $arvoKysely);
    $arvoKyselynTulokset = mysqli_query($conn, $arvoKysely);
}

$conn->close();
?>

<!DOCTYPE html>
<html>
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <link rel="stylesheet" href="http://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css">
        <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.12.0/jquery.min.js"></script>
        <script src="http://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/js/bootstrap.min.js"></script>
        <title>Harkkatyö</title>

    </head>
    <body>

        <div class="container">
            <form action="harkkatyo.php" method="POST">

                <div class="row form-group">
                    <div class="col-md-2"></div>
                    <div class="col-md-2">
                        <label>Alkupäivämäärä:</label>
                        <select class="form-control" name="alkupvm">
                            <?php
                            if (PaivamaaraAsetettu()) {
                                echo "<option value=''><p style='text-color:grey'>{$_REQUEST['alkupvm']}</p> </option>";
                            } else {
                                echo "<option value=''>-alkupvm-</option>";
                            }
                            while ($row = mysqli_fetch_assoc($paivatTulokset)) {
                                echo "<option value='{$row['pvm']}'>{$row['pvm']}</option>";
                            }
                            ?> 
                        </select>  
                    </div>
                    <div class="col-md-2"> 
                        <label>Minimi lämpötila:</label>
                        <input type="text" class="form-control" name="MinLampotila" placeholder="<?php echo "{$_REQUEST['MinLampotila']}" ?>">         
                    </div> 
                    <div  class="col-md-2">
                        <label>Minimi tuulennopeus:</label>
                        <input type="text" class="form-control" name="MinTuulennopeus" placeholder="<?php echo "{$_REQUEST['MinTuulennopeus']}" ?>">
                    </div>
                    <div class="col-md-2"></div>
                    <div class="col-md-2"></div>
                </div>

                <div class="row form-group">
                    <div class="col-md-2"></div>
                    <div class="col-md-2">
                        <label>Loppupäivämäärä</label>
                        <select class="form-control" name="loppupvm">
                            <?php
                            if (PaivamaaraAsetettu()) {
                                echo "<option value='' style='text-color:grey'>{$_REQUEST['loppupvm']}</option>";
                            } else {
                                echo "<option value=''>-loppupvm-</option>";
                            }

                            mysqli_data_seek($paivatTulokset, 0);   // nollataan pointteri
                            while ($row = mysqli_fetch_assoc($paivatTulokset)) {
                                echo "<option value='{$row['pvm']}'>{$row['pvm']}</option>";
                            }
                            ?>
                        </select> 
                    </div>
                    <div class="col-md-2"> 
                        <label>Maksimi lämpötila:</label>
                        <input type="text" class="form-control" name="MaxLampotila" placeholder="<?php echo "{$_REQUEST['MaxLampotila']}" ?>">
                    </div> 
                    <div class="col-md-2">
                        <label>Maksimi tuulennopeus:</label>
                        <input type="text" class="form-control" name="MaxTuulennopeus" placeholder="<?php echo "{$_REQUEST['ManTuulennopeus']}" ?>">
                    </div>
                    <div class="col-md-2"></div>
                    <div class="col-md-2"></div>
                </div>

                <div class="row form-group">
                    <div class="col-md-2"></div>
                    <div class="col-md-2">
                        <button type="submit" class="btn  btn-default">Aseta rajat / näytä kaikki</button>
                    </div>
                    <div class="col-md-2"></div> 
                    <div class="col-md-2"></div>
                    <div class="col-md-2"></div>
                    <div class="col-md-2"></div>
                </div>
            </form>
        </div>


        <div class="container">
            <div class="row">
                <div class="col-md-1"></div>
                <div class="col-md-10">
                    <table class="table table-hover table-responsive">
                        <thead>
                            <tr>
                                <th> </th>
                                <th>Pienin arvo</th>
                                <th>Suurin arvo</th>
                                <th>Keskiarvo</th>
                            </tr>
                        </thead>
                        <?php
                        while ($row2 = mysqli_fetch_assoc($tilastoKyselynTulokset)) {
                            echo "  <tr bgcolor='#e6f9ff'> <td align='centered'>Tuulen nopeus 1</td> <td> {$row2['MIN(tuulennopeus1)']} </td> <td> {$row2['MAX(tuulennopeus1)']} </td> <td> {$row2['AVG(tuulennopeus1)']} </td> </tr> 
                            <tr> <td>Tuulen nopeus 2</td> <td> {$row2['MIN(tuulennopeus2)']} </td> <td> {$row2['MAX(tuulennopeus2)']} </td> <td> {$row2['AVG(tuulennopeus2)']} </td> </tr> 
                            <tr bgcolor='#e6f9ff'> <td>Tuulen suunta 1</td> <td> {$row2['MIN(tuulensuunta1)']} </td> <td> {$row2['MAX(tuulensuunta1)']} </td> <td> {$row2['AVG(tuulensuunta1)']} </td> </tr>
                            <tr><td>Tuulen suunta 2</td> <td> {$row2['MIN(tuulensuunta2)']} </td> <td> {$row2['MAX(tuulensuunta2)']} </td> <td> {$row2['AVG(tuulensuunta2)']} </td> </tr>
                            <tr bgcolor='#e6f9ff'> <td>Sademäärä 1</td> <td> {$row2['MIN(sademaara1)']} </td> <td> {$row2['MAX(sademaara1)']} </td> <td> {$row2['AVG(sademaara1)']} </td> </tr>
                            <tr> <td>Sademäärä 2</td> <td> {$row2['MIN(sademaara2)']} </td> <td> {$row2['MAX(sademaara2)']} </td> <td> {$row2['AVG(sademaara2)']} </td> </tr>
                            <tr bgcolor='#e6f9ff'> <td>Ulkolämpötila 1</td> <td> {$row2['MIN(ulkolampotila1)']} </td> <td> {$row2['MAX(ulkolampotila1)']} </td> <td> {$row2['AVG(ulkolampotila1)']} </td> </tr>
                            <tr> <td>Ulkolämpötila 2</td> <td> {$row2['MIN(ulkolampotila2)']} </td> <td> {$row2['MAX(ulkolampotila2)']} </td> <td> {$row2['AVG(ulkolampotila2)']} </td> </tr>
                            <tr bgcolor='#e6f9ff'> <td>Ulkoilman kosteus</td> <td> {$row2['MIN(ulkoilmankosteus)']} </td> <td> {$row2['MAX(ulkoilmankosteus)']} </td> <td> {$row2['AVG(ulkoilmankosteus)']} </td> </tr>
                            <tr> <td>Sisäilman kosteus</td> <td> {$row2['MIN(sisailmankosteus)']} </td> <td> {$row2['MAX(sisailmankosteus)']} </td> <td> {$row2['AVG(sisailmankosteus)']} </td> </tr>
                            <tr bgcolor='#e6f9ff'> <td>Ilmanpaine</td> <td> {$row2['MIN(ilmanpaine)']} </td> <td> {$row2['MAX(ilmanpaine)']} </td> <td> {$row2['AVG(ilmanpaine)']} </td> </tr>";
                        }
                        ?>
                    </table>
                </div>
                <div class="col-md-1"></div> 
            </div>
        </div>

        <br>

        <table class="table table-hover table-responsive">
            <thead>
                <tr>
                    <?php
// Tulostetaan otsakkeet kun hakuja/lajitteluja on tehty ja sarakelajittelu tehdään ensimmäisen kerran.
                    if ($_SERVER["REQUEST_METHOD"] == "POST") {
                        if ($_REQUEST['lajittelu'] == "ASC") {
                            echo '<th><a href="harkkatyo.php?lajittelu=DESC&sarake=pvm&sarakejarjestykseen=true&alkupvm=' . $_REQUEST['alkupvm'] . '&loppupvm=' . $_REQUEST['loppupvm'] . '&MinTuulennopeus=' . $_REQUEST['MinTuulennopeus'] . '&MaxTuulennopeus=' . $_REQUEST['MaxTuulennopeus'] . '&MinLampotila=' . $_REQUEST['MinLampotila'] . '&MaxLampotila=' . $_REQUEST['MaxLampotila'] . '">Päivämäärä</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=DESC&sarake=kellonaika&sarakejarjestykseen=true&alkupvm=' . $_REQUEST['alkupvm'] . '&loppupvm=' . $_REQUEST['loppupvm'] . '&MinTuulennopeus=' . $_REQUEST['MinTuulennopeus'] . '&MaxTuulennopeus=' . $_REQUEST['MaxTuulennopeus'] . '&MinLampotila=' . $_REQUEST['MinLampotila'] . '&MaxLampotila=' . $_REQUEST['MaxLampotila'] . '">Kellonaika<</a>/th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=DESC&sarake=tuulennopeus1&sarakejarjestykseen=true&alkupvm=' . $_REQUEST['alkupvm'] . '&loppupvm=' . $_REQUEST['loppupvm'] . '&MinTuulennopeus=' . $_REQUEST['MinTuulennopeus'] . '&MaxTuulennopeus=' . $_REQUEST['MaxTuulennopeus'] . '&MinLampotila=' . $_REQUEST['MinLampotila'] . '&MaxLampotila=' . $_REQUEST['MaxLampotila'] . '">Tuulen nopeus 1</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=DESC&sarake=tuulennopeus2&sarakejarjestykseen=true&alkupvm=' . $_REQUEST['alkupvm'] . '&loppupvm=' . $_REQUEST['loppupvm'] . '&MinTuulennopeus=' . $_REQUEST['MinTuulennopeus'] . '&MaxTuulennopeus=' . $_REQUEST['MaxTuulennopeus'] . '&MinLampotila=' . $_REQUEST['MinLampotila'] . '&MaxLampotila=' . $_REQUEST['MaxLampotila'] . '">Tuulen nopeus 2</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=DESC&sarake=tuulensuunta1&sarakejarjestykseen=true&alkupvm=' . $_REQUEST['alkupvm'] . '&loppupvm=' . $_REQUEST['loppupvm'] . '&MinTuulennopeus=' . $_REQUEST['MinTuulennopeus'] . '&MaxTuulennopeus=' . $_REQUEST['MaxTuulennopeus'] . '&MinLampotila=' . $_REQUEST['MinLampotila'] . '&MaxLampotila=' . $_REQUEST['MaxLampotila'] . '">Tuulen suunta 1</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=DESC&sarake=tuulensuunta2&sarakejarjestykseen=true&alkupvm=' . $_REQUEST['alkupvm'] . '&loppupvm=' . $_REQUEST['loppupvm'] . '&MinTuulennopeus=' . $_REQUEST['MinTuulennopeus'] . '&MaxTuulennopeus=' . $_REQUEST['MaxTuulennopeus'] . '&MinLampotila=' . $_REQUEST['MinLampotila'] . '&MaxLampotila=' . $_REQUEST['MaxLampotila'] . '">Tuulen suunta 2</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=DESC&sarake=sademaara1&sarakejarjestykseen=true&alkupvm=' . $_REQUEST['alkupvm'] . '&loppupvm=' . $_REQUEST['loppupvm'] . '&MinTuulennopeus=' . $_REQUEST['MinTuulennopeus'] . '&MaxTuulennopeus=' . $_REQUEST['MaxTuulennopeus'] . '&MinLampotila=' . $_REQUEST['MinLampotila'] . '&MaxLampotila=' . $_REQUEST['MaxLampotila'] . '">Sademäärä 1</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=DESC&sarake=sademaara2&sarakejarjestykseen=true&alkupvm=' . $_REQUEST['alkupvm'] . '&loppupvm=' . $_REQUEST['loppupvm'] . '&MinTuulennopeus=' . $_REQUEST['MinTuulennopeus'] . '&MaxTuulennopeus=' . $_REQUEST['MaxTuulennopeus'] . '&MinLampotila=' . $_REQUEST['MinLampotila'] . '&MaxLampotila=' . $_REQUEST['MaxLampotila'] . '">Sademäärä 2</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=DESC&sarake=ulkolampotila1&sarakejarjestykseen=true&alkupvm=' . $_REQUEST['alkupvm'] . '&loppupvm=' . $_REQUEST['loppupvm'] . '&MinTuulennopeus=' . $_REQUEST['MinTuulennopeus'] . '&MaxTuulennopeus=' . $_REQUEST['MaxTuulennopeus'] . '&MinLampotila=' . $_REQUEST['MinLampotila'] . '&MaxLampotila=' . $_REQUEST['MaxLampotila'] . '">Ulkolämpötila 1</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=DESC&sarake=ulkolampotila2&sarakejarjestykseen=true&alkupvm=' . $_REQUEST['alkupvm'] . '&loppupvm=' . $_REQUEST['loppupvm'] . '&MinTuulennopeus=' . $_REQUEST['MinTuulennopeus'] . '&MaxTuulennopeus=' . $_REQUEST['MaxTuulennopeus'] . '&MinLampotila=' . $_REQUEST['MinLampotila'] . '&MaxLampotila=' . $_REQUEST['MaxLampotila'] . '">Ulkolämpötila 2</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=DESC&sarake=ulkoilmankosteus&sarakejarjestykseen=true&alkupvm=' . $_REQUEST['alkupvm'] . '&loppupvm=' . $_REQUEST['loppupvm'] . '&MinTuulennopeus=' . $_REQUEST['MinTuulennopeus'] . '&MaxTuulennopeus=' . $_REQUEST['MaxTuulennopeus'] . '&MinLampotila=' . $_REQUEST['MinLampotila'] . '&MaxLampotila=' . $_REQUEST['MaxLampotila'] . '">Ulkoilman kosteus</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=DESC&sarake=sisailmankosteus&sarakejarjestykseen=true&alkupvm=' . $_REQUEST['alkupvm'] . '&loppupvm=' . $_REQUEST['loppupvm'] . '&MinTuulennopeus=' . $_REQUEST['MinTuulennopeus'] . '&MaxTuulennopeus=' . $_REQUEST['MaxTuulennopeus'] . '&MinLampotila=' . $_REQUEST['MinLampotila'] . '&MaxLampotila=' . $_REQUEST['MaxLampotila'] . '">Sisäilman kosteus</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=DESC&sarake=ilmanpaine&sarakejarjestykseen=true&alkupvm=' . $_REQUEST['alkupvm'] . '&loppupvm=' . $_REQUEST['loppupvm'] . '&MinTuulennopeus=' . $_REQUEST['MinTuulennopeus'] . '&MaxTuulennopeus=' . $_REQUEST['MaxTuulennopeus'] . '&MinLampotila=' . $_REQUEST['MinLampotila'] . '&MaxLampotila=' . $_REQUEST['MaxLampotila'] . '">Ilmanpaine</a></th>';
                        } else {
                            echo '<th><a href="harkkatyo.php?lajittelu=ASC&sarake=pvm&sarakejarjestykseen=true&alkupvm=' . $_REQUEST['alkupvm'] . '&loppupvm=' . $_REQUEST['loppupvm'] . '&MinTuulennopeus=' . $_REQUEST['MinTuulennopeus'] . '&MaxTuulennopeus=' . $_REQUEST['MaxTuulennopeus'] . '&MinLampotila=' . $_REQUEST['MinLampotila'] . '&MaxLampotila=' . $_REQUEST['MaxLampotila'] . '">Päivämäärä</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=ASC&sarake=kellonaika&sarakejarjestykseen=true&alkupvm=' . $_REQUEST['alkupvm'] . '&loppupvm=' . $_REQUEST['loppupvm'] . '&MinTuulennopeus=' . $_REQUEST['MinTuulennopeus'] . '&MaxTuulennopeus=' . $_REQUEST['MaxTuulennopeus'] . '&MinLampotila=' . $_REQUEST['MinLampotila'] . '&MaxLampotila=' . $_REQUEST['MaxLampotila'] . '">Kellonaika</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=ASC&sarake=kellonaika&sarakejarjestykseen=true&alkupvm=' . $_REQUEST['alkupvm'] . '&loppupvm=' . $_REQUEST['loppupvm'] . '&MinTuulennopeus=' . $_REQUEST['MinTuulennopeus'] . '&MaxTuulennopeus=' . $_REQUEST['MaxTuulennopeus'] . '&MinLampotila=' . $_REQUEST['MinLampotila'] . '&MaxLampotila=' . $_REQUEST['MaxLampotila'] . '">Tuulen nopeus 1</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=ASC&sarake=tuulennopeus2&sarakejarjestykseen=true&alkupvm=' . $_REQUEST['alkupvm'] . '&loppupvm=' . $_REQUEST['loppupvm'] . '&MinTuulennopeus=' . $_REQUEST['MinTuulennopeus'] . '&MaxTuulennopeus=' . $_REQUEST['MaxTuulennopeus'] . '&MinLampotila=' . $_REQUEST['MinLampotila'] . '&MaxLampotila=' . $_REQUEST['MaxLampotila'] . '">Tuulen nopeus 2</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=ASC&sarake=tuulensuunta1&sarakejarjestykseen=true&alkupvm=' . $_REQUEST['alkupvm'] . '&loppupvm=' . $_REQUEST['loppupvm'] . '&MinTuulennopeus=' . $_REQUEST['MinTuulennopeus'] . '&MaxTuulennopeus=' . $_REQUEST['MaxTuulennopeus'] . '&MinLampotila=' . $_REQUEST['MinLampotila'] . '&MaxLampotila=' . $_REQUEST['MaxLampotila'] . '">Tuulen suunta 1</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=ASC&sarake=tuulensuunta2&sarakejarjestykseen=true&alkupvm=' . $_REQUEST['alkupvm'] . '&loppupvm=' . $_REQUEST['loppupvm'] . '&MinTuulennopeus=' . $_REQUEST['MinTuulennopeus'] . '&MaxTuulennopeus=' . $_REQUEST['MaxTuulennopeus'] . '&MinLampotila=' . $_REQUEST['MinLampotila'] . '&MaxLampotila=' . $_REQUEST['MaxLampotila'] . '">Tuulen suunta 2</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=ASC&sarake=sademaara1&sarakejarjestykseen=true&alkupvm=' . $_REQUEST['alkupvm'] . '&loppupvm=' . $_REQUEST['loppupvm'] . '&MinTuulennopeus=' . $_REQUEST['MinTuulennopeus'] . '&MaxTuulennopeus=' . $_REQUEST['MaxTuulennopeus'] . '&MinLampotila=' . $_REQUEST['MinLampotila'] . '&MaxLampotila=' . $_REQUEST['MaxLampotila'] . '">Sademäärä 1</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=ASC&sarake=sademaara2&sarakejarjestykseen=true&alkupvm=' . $_REQUEST['alkupvm'] . '&loppupvm=' . $_REQUEST['loppupvm'] . '&MinTuulennopeus=' . $_REQUEST['MinTuulennopeus'] . '&MaxTuulennopeus=' . $_REQUEST['MaxTuulennopeus'] . '&MinLampotila=' . $_REQUEST['MinLampotila'] . '&MaxLampotila=' . $_REQUEST['MaxLampotila'] . '">Sademäärä 2</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=ASC&sarake=ulkolampotila1&sarakejarjestykseen=true&alkupvm=' . $_REQUEST['alkupvm'] . '&loppupvm=' . $_REQUEST['loppupvm'] . '&MinTuulennopeus=' . $_REQUEST['MinTuulennopeus'] . '&MaxTuulennopeus=' . $_REQUEST['MaxTuulennopeus'] . '&MinLampotila=' . $_REQUEST['MinLampotila'] . '&MaxLampotila=' . $_REQUEST['MaxLampotila'] . '">Ulkolämpötila 1</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=ASC&sarake=ulkolampotila2&sarakejarjestykseen=true&alkupvm=' . $_REQUEST['alkupvm'] . '&loppupvm=' . $_REQUEST['loppupvm'] . '&MinTuulennopeus=' . $_REQUEST['MinTuulennopeus'] . '&MaxTuulennopeus=' . $_REQUEST['MaxTuulennopeus'] . '&MinLampotila=' . $_REQUEST['MinLampotila'] . '&MaxLampotila=' . $_REQUEST['MaxLampotila'] . '">Ulkolämpötila 2</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=ASC&sarake=ulkoilmankosteus&sarakejarjestykseen=true&alkupvm=' . $_REQUEST['alkupvm'] . '&loppupvm=' . $_REQUEST['loppupvm'] . '&MinTuulennopeus=' . $_REQUEST['MinTuulennopeus'] . '&MaxTuulennopeus=' . $_REQUEST['MaxTuulennopeus'] . '&MinLampotila=' . $_REQUEST['MinLampotila'] . '&MaxLampotila=' . $_REQUEST['MaxLampotila'] . '">Ulkoilman kosteus</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=ASC&sarake=sisailmankosteus&sarakejarjestykseen=true&alkupvm=' . $_REQUEST['alkupvm'] . '&loppupvm=' . $_REQUEST['loppupvm'] . '&MinTuulennopeus=' . $_REQUEST['MinTuulennopeus'] . '&MaxTuulennopeus=' . $_REQUEST['MaxTuulennopeus'] . '&MinLampotila=' . $_REQUEST['MinLampotila'] . '&MaxLampotila=' . $_REQUEST['MaxLampotila'] . '">Sisailman kosteus</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=ASC&sarake=ilmanpaine&sarakejarjestykseen=true&alkupvm=' . $_REQUEST['alkupvm'] . '&loppupvm=' . $_REQUEST['loppupvm'] . '&MinTuulennopeus=' . $_REQUEST['MinTuulennopeus'] . '&MaxTuulennopeus=' . $_REQUEST['MaxTuulennopeus'] . '&MinLampotila=' . $_REQUEST['MinLampotila'] . '&MaxLampotila=' . $_REQUEST['MaxLampotila'] . '">Ilmanpaine</a></th>';
                        }
                        // Tulostetaan otsakkeet kun hakuja/lajitteluja on tehty ja sarakelajittelu on tehty jo kerran.
                    } else if ($_REQUEST['sarakejarjestykseen'] == "true") {
                        if ($_REQUEST['lajittelu'] == "ASC") {
                            echo '<th><a href="harkkatyo.php?lajittelu=DESC&sarake=pvm&sarakejarjestykseen=true&alkupvm=' . $_REQUEST['alkupvm'] . '&loppupvm=' . $_REQUEST['loppupvm'] . '&MinTuulennopeus=' . $_REQUEST['MinTuulennopeus'] . '&MaxTuulennopeus=' . $_REQUEST['MaxTuulennopeus'] . '&MinLampotila=' . $_REQUEST['MinLampotila'] . '&MaxLampotila=' . $_REQUEST['MaxLampotila'] . '">Päivämäärä</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=DESC&sarake=kellonaika&sarakejarjestykseen=true&alkupvm=' . $_REQUEST['alkupvm'] . '&loppupvm=' . $_REQUEST['loppupvm'] . '&MinTuulennopeus=' . $_REQUEST['MinTuulennopeus'] . '&MaxTuulennopeus=' . $_REQUEST['MaxTuulennopeus'] . '&MinLampotila=' . $_REQUEST['MinLampotila'] . '&MaxLampotila=' . $_REQUEST['MaxLampotila'] . '">Kellonaika</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=DESC&sarake=tuulennopeus1&sarakejarjestykseen=true&alkupvm=' . $_REQUEST['alkupvm'] . '&loppupvm=' . $_REQUEST['loppupvm'] . '&MinTuulennopeus=' . $_REQUEST['MinTuulennopeus'] . '&MaxTuulennopeus=' . $_REQUEST['MaxTuulennopeus'] . '&MinLampotila=' . $_REQUEST['MinLampotila'] . '&MaxLampotila=' . $_REQUEST['MaxLampotila'] . '">Tuulen nopeus 1</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=DESC&sarake=tuulennopeus2&sarakejarjestykseen=true&alkupvm=' . $_REQUEST['alkupvm'] . '&loppupvm=' . $_REQUEST['loppupvm'] . '&MinTuulennopeus=' . $_REQUEST['MinTuulennopeus'] . '&MaxTuulennopeus=' . $_REQUEST['MaxTuulennopeus'] . '&MinLampotila=' . $_REQUEST['MinLampotila'] . '&MaxLampotila=' . $_REQUEST['MaxLampotila'] . '">Tuulen nopeus 2</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=DESC&sarake=tuulensuunta1&sarakejarjestykseen=true&alkupvm=' . $_REQUEST['alkupvm'] . '&loppupvm=' . $_REQUEST['loppupvm'] . '&MinTuulennopeus=' . $_REQUEST['MinTuulennopeus'] . '&MaxTuulennopeus=' . $_REQUEST['MaxTuulennopeus'] . '&MinLampotila=' . $_REQUEST['MinLampotila'] . '&MaxLampotila=' . $_REQUEST['MaxLampotila'] . '">Tuulen suunta 1</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=DESC&sarake=tuulensuunta2&sarakejarjestykseen=true&alkupvm=' . $_REQUEST['alkupvm'] . '&loppupvm=' . $_REQUEST['loppupvm'] . '&MinTuulennopeus=' . $_REQUEST['MinTuulennopeus'] . '&MaxTuulennopeus=' . $_REQUEST['MaxTuulennopeus'] . '&MinLampotila=' . $_REQUEST['MinLampotila'] . '&MaxLampotila=' . $_REQUEST['MaxLampotila'] . '">Tuulen suunta 2</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=DESC&sarake=sademaara1&sarakejarjestykseen=true&alkupvm=' . $_REQUEST['alkupvm'] . '&loppupvm=' . $_REQUEST['loppupvm'] . '&MinTuulennopeus=' . $_REQUEST['MinTuulennopeus'] . '&MaxTuulennopeus=' . $_REQUEST['MaxTuulennopeus'] . '&MinLampotila=' . $_REQUEST['MinLampotila'] . '&MaxLampotila=' . $_REQUEST['MaxLampotila'] . '">Sademäärä 1</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=DESC&sarake=sademaara2&sarakejarjestykseen=true&alkupvm=' . $_REQUEST['alkupvm'] . '&loppupvm=' . $_REQUEST['loppupvm'] . '&MinTuulennopeus=' . $_REQUEST['MinTuulennopeus'] . '&MaxTuulennopeus=' . $_REQUEST['MaxTuulennopeus'] . '&MinLampotila=' . $_REQUEST['MinLampotila'] . '&MaxLampotila=' . $_REQUEST['MaxLampotila'] . '">Sademäärä 2</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=DESC&sarake=ulkolampotila1&sarakejarjestykseen=true&alkupvm=' . $_REQUEST['alkupvm'] . '&loppupvm=' . $_REQUEST['loppupvm'] . '&MinTuulennopeus=' . $_REQUEST['MinTuulennopeus'] . '&MaxTuulennopeus=' . $_REQUEST['MaxTuulennopeus'] . '&MinLampotila=' . $_REQUEST['MinLampotila'] . '&MaxLampotila=' . $_REQUEST['MaxLampotila'] . '">Ulkolämpötila 1</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=DESC&sarake=ulkolampotila2&sarakejarjestykseen=true&alkupvm=' . $_REQUEST['alkupvm'] . '&loppupvm=' . $_REQUEST['loppupvm'] . '&MinTuulennopeus=' . $_REQUEST['MinTuulennopeus'] . '&MaxTuulennopeus=' . $_REQUEST['MaxTuulennopeus'] . '&MinLampotila=' . $_REQUEST['MinLampotila'] . '&MaxLampotila=' . $_REQUEST['MaxLampotila'] . '">Ulkolämpötila 2</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=DESC&sarake=ulkoilmankosteus&sarakejarjestykseen=true&alkupvm=' . $_REQUEST['alkupvm'] . '&loppupvm=' . $_REQUEST['loppupvm'] . '&MinTuulennopeus=' . $_REQUEST['MinTuulennopeus'] . '&MaxTuulennopeus=' . $_REQUEST['MaxTuulennopeus'] . '&MinLampotila=' . $_REQUEST['MinLampotila'] . '&MaxLampotila=' . $_REQUEST['MaxLampotila'] . '">Ulkoilman kosteus</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=DESC&sarake=sisailmankosteus&sarakejarjestykseen=true&alkupvm=' . $_REQUEST['alkupvm'] . '&loppupvm=' . $_REQUEST['loppupvm'] . '&MinTuulennopeus=' . $_REQUEST['MinTuulennopeus'] . '&MaxTuulennopeus=' . $_REQUEST['MaxTuulennopeus'] . '&MinLampotila=' . $_REQUEST['MinLampotila'] . '&MaxLampotila=' . $_REQUEST['MaxLampotila'] . '">Sisailman kosteus</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=DESC&sarake=ilmanpaine&sarakejarjestykseen=true&alkupvm=' . $_REQUEST['alkupvm'] . '&loppupvm=' . $_REQUEST['loppupvm'] . '&MinTuulennopeus=' . $_REQUEST['MinTuulennopeus'] . '&MaxTuulennopeus=' . $_REQUEST['MaxTuulennopeus'] . '&MinLampotila=' . $_REQUEST['MinLampotila'] . '&MaxLampotila=' . $_REQUEST['MaxLampotila'] . '">Ilmanpaine</a></th>';
                        } else {
                            echo '<th><a href="harkkatyo.php?lajittelu=ASC&sarake=pvm&sarakejarjestykseen=true&alkupvm=' . $_REQUEST['alkupvm'] . '&loppupvm=' . $_REQUEST['loppupvm'] . '&MinTuulennopeus=' . $_REQUEST['MinTuulennopeus'] . '&MaxTuulennopeus=' . $_REQUEST['MaxTuulennopeus'] . '&MinLampotila=' . $_REQUEST['MinLampotila'] . '&MaxLampotila=' . $_REQUEST['MaxLampotila'] . '">Päivämäärä</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=ASC&sarake=kellonaika&sarakejarjestykseen=true&alkupvm=' . $_REQUEST['alkupvm'] . '&loppupvm=' . $_REQUEST['loppupvm'] . '&MinTuulennopeus=' . $_REQUEST['MinTuulennopeus'] . '&MaxTuulennopeus=' . $_REQUEST['MaxTuulennopeus'] . '&MinLampotila=' . $_REQUEST['MinLampotila'] . '&MaxLampotila=' . $_REQUEST['MaxLampotila'] . '">Kellonaika</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=ASC&sarake=tuulennopeus1&sarakejarjestykseen=true&alkupvm=' . $_REQUEST['alkupvm'] . '&loppupvm=' . $_REQUEST['loppupvm'] . '&MinTuulennopeus=' . $_REQUEST['MinTuulennopeus'] . '&MaxTuulennopeus=' . $_REQUEST['MaxTuulennopeus'] . '&MinLampotila=' . $_REQUEST['MinLampotila'] . '&MaxLampotila=' . $_REQUEST['MaxLampotila'] . '">Tuulen nopeus 1</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=ASC&sarake=tuulennopeus2&sarakejarjestykseen=true&alkupvm=' . $_REQUEST['alkupvm'] . '&loppupvm=' . $_REQUEST['loppupvm'] . '&MinTuulennopeus=' . $_REQUEST['MinTuulennopeus'] . '&MaxTuulennopeus=' . $_REQUEST['MaxTuulennopeus'] . '&MinLampotila=' . $_REQUEST['MinLampotila'] . '&MaxLampotila=' . $_REQUEST['MaxLampotila'] . '">Tuulen nopeus 2</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=ASC&sarake=tuulensuunta1&sarakejarjestykseen=true&alkupvm=' . $_REQUEST['alkupvm'] . '&loppupvm=' . $_REQUEST['loppupvm'] . '&MinTuulennopeus=' . $_REQUEST['MinTuulennopeus'] . '&MaxTuulennopeus=' . $_REQUEST['MaxTuulennopeus'] . '&MinLampotila=' . $_REQUEST['MinLampotila'] . '&MaxLampotila=' . $_REQUEST['MaxLampotila'] . '">Tuulen suunta 1</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=ASC&sarake=tuulensuunta2&sarakejarjestykseen=true&alkupvm=' . $_REQUEST['alkupvm'] . '&loppupvm=' . $_REQUEST['loppupvm'] . '&MinTuulennopeus=' . $_REQUEST['MinTuulennopeus'] . '&MaxTuulennopeus=' . $_REQUEST['MaxTuulennopeus'] . '&MinLampotila=' . $_REQUEST['MinLampotila'] . '&MaxLampotila=' . $_REQUEST['MaxLampotila'] . '">Tuulen suunta 2</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=ASC&sarake=sademaara1&sarakejarjestykseen=true&alkupvm=' . $_REQUEST['alkupvm'] . '&loppupvm=' . $_REQUEST['loppupvm'] . '&MinTuulennopeus=' . $_REQUEST['MinTuulennopeus'] . '&MaxTuulennopeus=' . $_REQUEST['MaxTuulennopeus'] . '&MinLampotila=' . $_REQUEST['MinLampotila'] . '&MaxLampotila=' . $_REQUEST['MaxLampotila'] . '">Sademäärä 1</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=ASC&sarake=sademaara2&sarakejarjestykseen=true&alkupvm=' . $_REQUEST['alkupvm'] . '&loppupvm=' . $_REQUEST['loppupvm'] . '&MinTuulennopeus=' . $_REQUEST['MinTuulennopeus'] . '&MaxTuulennopeus=' . $_REQUEST['MaxTuulennopeus'] . '&MinLampotila=' . $_REQUEST['MinLampotila'] . '&MaxLampotila=' . $_REQUEST['MaxLampotila'] . '">Sademäärä 2</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=ASC&sarake=ulkolampotila1&sarakejarjestykseen=true&alkupvm=' . $_REQUEST['alkupvm'] . '&loppupvm=' . $_REQUEST['loppupvm'] . '&MinTuulennopeus=' . $_REQUEST['MinTuulennopeus'] . '&MaxTuulennopeus=' . $_REQUEST['MaxTuulennopeus'] . '&MinLampotila=' . $_REQUEST['MinLampotila'] . '&MaxLampotila=' . $_REQUEST['MaxLampotila'] . '">Ulkolämpötila 1</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=ASC&sarake=ulkolampotila2&sarakejarjestykseen=true&alkupvm=' . $_REQUEST['alkupvm'] . '&loppupvm=' . $_REQUEST['loppupvm'] . '&MinTuulennopeus=' . $_REQUEST['MinTuulennopeus'] . '&MaxTuulennopeus=' . $_REQUEST['MaxTuulennopeus'] . '&MinLampotila=' . $_REQUEST['MinLampotila'] . '&MaxLampotila=' . $_REQUEST['MaxLampotila'] . '">Ulkolämpötila 2</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=ASC&sarake=ulkoilmankosteus&sarakejarjestykseen=true&alkupvm=' . $_REQUEST['alkupvm'] . '&loppupvm=' . $_REQUEST['loppupvm'] . '&MinTuulennopeus=' . $_REQUEST['MinTuulennopeus'] . '&MaxTuulennopeus=' . $_REQUEST['MaxTuulennopeus'] . '&MinLampotila=' . $_REQUEST['MinLampotila'] . '&MaxLampotila=' . $_REQUEST['MaxLampotila'] . '">Ulkoilman kosteus</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=ASC&sarake=sisailmankosteus&sarakejarjestykseen=true&alkupvm=' . $_REQUEST['alkupvm'] . '&loppupvm=' . $_REQUEST['loppupvm'] . '&MinTuulennopeus=' . $_REQUEST['MinTuulennopeus'] . '&MaxTuulennopeus=' . $_REQUEST['MaxTuulennopeus'] . '&MinLampotila=' . $_REQUEST['MinLampotila'] . '&MaxLampotila=' . $_REQUEST['MaxLampotila'] . '">Sisailman kosteus</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=ASC&sarake=ilmanpaine&sarakejarjestykseen=true&alkupvm=' . $_REQUEST['alkupvm'] . '&loppupvm=' . $_REQUEST['loppupvm'] . '&MinTuulennopeus=' . $_REQUEST['MinTuulennopeus'] . '&MaxTuulennopeus=' . $_REQUEST['MaxTuulennopeus'] . '&MinLampotila=' . $_REQUEST['MinLampotila'] . '&MaxLampotila=' . $_REQUEST['MaxLampotila'] . '">Ilmanpaine</a></th>';
                        }
                    } else {
                        // tulostetaan otsakkeet kun mitään raja-arvoja ei ole asetettu
                        if ($_REQUEST['lajittelu'] == "ASC") {
                            echo '<th><a href="harkkatyo.php?lajittelu=DESC&sarake=pvm&sarakejarjestykseen=true">Päivämäärä</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=DESC&sarake=kellonaika&sarakejarjestykseen=true">Kellonaika</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=DESC&sarake=tuulennopeus1&sarakejarjestykseen=true">Tuulen nopeus 1</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=DESC&sarake=tuulennopeus2&sarakejarjestykseen=true">Tuulen nopeus 2</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=DESC&sarake=tuulensuunta1&sarakejarjestykseen=true">Tuulen suunta 1</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=DESC&sarake=tuulensuunta2&sarakejarjestykseen=true">Tuulen suunta 2</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=DESC&sarake=sademaara1&sarakejarjestykseen=true">Sademäärä 1</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=DESC&sarake=sademaara2&sarakejarjestykseen=true">Sademärä 2</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=DESC&sarake=ulkolampotila1&sarakejarjestykseen=true">Ulkolämpötila 1</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=DESC&sarake=ulkolampotila2&sarakejarjestykseen=true">Ulkolämpötila 2</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=DESC&sarake=ulkoilmankosteus&sarakejarjestykseen=true">Ulkoilman kosteus</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=DESC&sarake=sisailmankosteus&sarakejarjestykseen=true">Sisailman kosteus</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=DESC&sarake=ilmanpaine&sarakejarjestykseen=true">Ilmanpaine</a></th>';
                        } else {
                            echo '<th><a href="harkkatyo.php?lajittelu=ASC&sarake=pvm&sarakejarjestykseen=true">Päivämäärä</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=ASC&sarake=kellonaika&sarakejarjestykseen=true">Kellonaika</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=ASC&sarake=tuulennopeus1&sarakejarjestykseen=true">Tuulen nopeus 1</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=ASC&sarake=tuulennopeus2&sarakejarjestykseen=true">Tuulen nopeus 2</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=ASC&sarake=tuulensuunta1&sarakejarjestykseen=true">Tuulen suunta 1</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=ASC&sarake=tuulensuunta2&sarakejarjestykseen=true">Tuulen suunta 2</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=ASC&sarake=sademaara1&sarakejarjestykseen=true">Sademäärä 1</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=ASC&sarake=sademaara2&sarakejarjestykseen=true">Sademäärä 2</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=ASC&sarake=ulkolampotila1&sarakejarjestykseen=true">Ulkolämpötila 1</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=ASC&sarake=ulkolampotila2&sarakejarjestykseen=true">Ulkolämpötila 2</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=ASC&sarake=ulkoilmankosteus&sarakejarjestykseen=true">Ulkoilman kosteus</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=ASC&sarake=sisailmankosteus&sarakejarjestykseen=true">Sisailman kosteus</a></th>';
                            echo '<th><a href="harkkatyo.php?lajittelu=ASC&sarake=ilmanpaine&sarakejarjestykseen=true">Ilmanpaine</a></th>';
                        }
                    }
                    ?>
                </tr>
            </thead>
            <?php
            $riviNro = 0;
            while ($row = mysqli_fetch_assoc($arvoKyselynTulokset)) {
                If ($riviNro % 2 == 0) {
                    echo "<tr>";
                    $riviNro++;
                } else {
                    echo "<tr bgcolor='#e6f9ff'>";
                    $riviNro++;
                }
                echo " <td> {$row['pvm']} </td> <td> {$row['kellonaika']} </td> <td> {$row['tuulennopeus1']} </td> <td> {$row['tuulennopeus2']} </td> <td> {$row['tuulensuunta1']} </td> 
                       <td> {$row['tuulensuunta2']} </td> <td> {$row['sademaara1']} </td> <td> {$row['sademaara2']} </td> <td> {$row['ulkolampotila1']} </td> 
                       <td> {$row['ulkolampotila2']} </td> <td>{$row['ulkoilmankosteus']}</td> <td>{$row['sisailmankosteus']}</td> <td>{$row['ilmanpaine']}</td> </tr> ";
            }
            ?>
        </table>
    </body>
</html>


<?php
//######################################################################################################################
//######################################################################################################################
?>
