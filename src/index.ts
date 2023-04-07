import express from "express"
import { UserTokenRequestData } from "./deserializer";
import { createBase64Token } from "./serializer";

const client = express()

client.use(express.json())

client.post("/api/user", async (req, res) => {
    const tokenRequest: UserTokenRequestData = req.body as UserTokenRequestData
    res.send(createBase64Token(tokenRequest))
    console.log(`Received POST @ /api/user : ${JSON.stringify(tokenRequest)}`)
})

client.put("/api/games", async (req, res) => {
    console.log(`Received PUT @ /api/games : ${JSON.stringify(req.body)}`)
    res.send({
        Ip: Buffer.from("127.0.0.1".split(".").map(x => parseInt(x))).readUInt32LE(0),
        Port: 22023
    })
})

const LISTEN = client.listen(22026, () => {
    console.log(`Started Among Us HTTP Server`)
})

process.on('SIGINT', () => {if (LISTEN.listening) LISTEN.close()})
process.on('SIGTERM', () => {if (LISTEN.listening) LISTEN.close()})