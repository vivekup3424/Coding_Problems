import type { Stage } from "./taskflow";

export interface ITemplate {
	name: string;
	context: object;
	options: object;
	stages: Stage[]
  }

export interface Template extends ITemplate {
	_id: string;
	templateId: string,
  }