// pragma solidity 0.8.20;

// import {HorseStore} from "../../src/horseStoreV1/HorseStore.sol";
// import {HorseStoreYul} from "../../src/horseStoreV1/HorseStoreYul.sol";
// import {Test, console2} from "forge-std/Test.sol";

// abstract contract Base_TestV1 is Test {
//     string public constant horseStoreLocation = "horseStoreV1/HorseStore";
//     HorseStore horseStoreHuff;
//     HorseStoreYul horseStoreYul;
//     HorseStore horseStoreSol;

//     function setUp() public virtual {
//         horseStoreYul = new HorseStoreYul();
//         horseStoreSol = new HorseStore();
//     }
// }

// SPDX-License-Identifier: MIT
pragma solidity 0.8.20;

import {Test, console2} from "forge-std/Test.sol";
import {HorseStore} from "../../src/horseStoreV1/HorseStore.sol";

abstract contract Base_TestV1 is Test {
    HorseStore public horseStore;

    function setUp() public virtual {
        horseStore = new HorseStore();
    }

    function testReadValue() public {
        uint256 value = horseStore.readNumberOfHorses();

        assertEq(value, 0, "Initial value should be 0");
    }

    function testWriteValue(uint256 numberOfHorses) public {
        horseStore.updateHorseNumber(numberOfHorses);

        assertEq(horseStore.readNumberOfHorses(), numberOfHorses, "Value should be updated");
    }
}
