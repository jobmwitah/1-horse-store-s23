//SPDX-Licence-Identifier: MIT
pragma solidity 0.8.20;

import {Base_TestV1, HorseStore} from "./Base_TestV1.t.sol";
import {YulDeployer} from "deploy-yul/YulDeployer.sol";

contract HorseStoreYul is Base_TestV1 {
    YulDeployer yulDeployer = new YulDeployer();

    function setUp() public override {
        horseStore = HorseStore(yulDeployer.deployContract("HorseStoreYul"));
    }
}
