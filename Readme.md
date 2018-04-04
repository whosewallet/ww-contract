# Setup whosewallet master account
1. Create key

```bash
cleos create key && cleos create key

Private key: 5Hr5nXogAsggpYzRfLXFXFyE4t4YfY29PhZzfgh7LoG3V9zBUsn
Public key: EOS6Uab5iaypSdc2dRAkvsFx1SD5s4U9zzG2c4PViiVZDzwuLTKeE

Private key: 5Kb4JsT35UtLBZ3G2WzALVP9LYrgTzoZg48igSN2dmKwxxGEBPN
Public key: EOS6f39NisBEiFpMCZ4LaBHmtCUQ8wKcccLAY1rzSE2R7ZNHTS4C2
```

2. Create account

```bash
cleos create account eosio whosewallet EOS6Uab5iaypSdc2dRAkvsFx1SD5s4U9zzG2c4PViiVZDzwuLTKeE EOS6f39NisBEiFpMCZ4LaBHmtCUQ8wKcccLAY1rzSE2R7ZNHTS4C2
```
__NOTE:__ _Remember to replace owner key and active key with your own_

# Build & deploy

```bash
$ sh build.sh
$ sh deploy.sh
````

# Pre-define

- Bitcoin address type: 50
- Ethereum address type: 100

# Sample

#### set a wallet for user
1. Create account: `acmv` and `haiz`

```bash
cleos create account whosewallet acmv EOS6Uab5iaypSdc2dRAkvsFx1SD5s4U9zzG2c4PViiVZDzwuLTKeE EOS6f39NisBEiFpMCZ4LaBHmtCUQ8wKcccLAY1rzSE2R7ZNHTS4C2

cleos create account whosewallet haiz EOS6Uab5iaypSdc2dRAkvsFx1SD5s4U9zzG2c4PViiVZDzwuLTKeE EOS6f39NisBEiFpMCZ4LaBHmtCUQ8wKcccLAY1rzSE2R7ZNHTS4C2
```

2. User `acmv` want to save his wallet address info `0x1a4C8627eeCf38d7392B7637123a899ff559f0A0`. This is an Ethereum address, so the type must be `100`.

```bash
cleos push action whosewallet inrnw '{ "w_add": "0x1a4C8627eeCf38d7392B7637123a899ff559f0A0", "w_type": "100", "a_name": "acmv" }' -p whosewallet@active -p acmv@active
```

3. User `haiz` want to save his wallet address info `12N22uVNofBYaNfjCSdzpVPcyd5Lfh11zq`. This is an Bitcoin address, so the type must be `50`.

```bash
cleos push action whosewallet inrnw '{ "w_add": "12N22uVNofBYaNfjCSdzpVPcyd5Lfh11zq", "w_type": "50", "a_name": "haiz" }' -p whosewallet@active -p haiz@active
```

4. Verify:

```bash
$ cleos get table whosewallet acmv wwallet

{
  "rows": [{
      "id": "1116012565360219490",
      "a_name": "",
      "w_type": 100,
      "w_add": "0x1a4C8627eeCf38d7392B7637123a899ff559f0A0"
    }
  ],
  "more": false
}

$ cleos get table whosewallet haiz wwallet

{
  "rows": [{
      "id": "4124316577211100456",
      "a_name": "",
      "w_type": 50,
      "w_add": "12N22uVNofBYaNfjCSdzpVPcyd5Lfh11zq"
    }
  ],
  "more": false
}

$ cleos get table whosewallet whosewallet wwallet

{
  "rows": [{
      "id": "3305419447951227220",
      "a_name": "acmv",
      "w_type": 100,
      "w_add": "0x1a4C8627eeCf38d7392B7637123a899ff559f0A0"
    },{
      "id": "4124316577211100456",
      "a_name": "haiz",
      "w_type": 50,
      "w_add": "12N22uVNofBYaNfjCSdzpVPcyd5Lfh11zq"
    }
  ],
  "more": false
}
```