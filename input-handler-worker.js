import { workerData } from "node:worker_threads";
import { sendInput } from "./input-handler.js";

sendInput(workerData);