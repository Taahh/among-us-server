import { UserTokenRequestData } from "./deserializer";
import crypto from "node:crypto"

const PRIVATE_KEY: Buffer = crypto.randomBytes(128)

interface MatchmakerTokenPayload {
    Puid: string,

    ClientVersion: number,

    ExpiresAt: string
}

interface MatchmakerToken {
    Content: MatchmakerTokenPayload,
    Hash: string
}

interface HostServer {
    Ip: string,
    Port: number
}


// With assistance from https://github.com/SkeldJS/Hindenburg/blob/6ace13a26b22083946af2ff9601172c6b0b145a2/src/matchmaker/Matchmaker.ts#L64
export function createBase64Token(tokenRequest: UserTokenRequestData): string {
    const payload: MatchmakerTokenPayload = {
        Puid: tokenRequest.Puid,
        ClientVersion: tokenRequest.ClientVersion,
        ExpiresAt: new Date().toISOString()
    }

    const payloadString = JSON.stringify(payload)
    const hash = crypto.createHmac("sha256", PRIVATE_KEY).update(payloadString).digest();

    const token: MatchmakerToken = {
        Content: payload,
        Hash: hash.toString("base64")
    }

    return Buffer.from(JSON.stringify(token), "utf8").toString("base64")
}