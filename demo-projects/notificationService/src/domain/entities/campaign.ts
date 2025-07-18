// General campaign targeting by event/properties
interface CampaignWhere {
    event_name?: string;
    from?: number; // YYYYMMDD
    to?: number;
    common_profile_properties?: {
        profile_fields?: Array<{
            name: string;
            operator: string;
            value: string | number;
        }>;
    };
}

// Conversion goal for campaign
interface CampaignConversionGoal {
    event_name: string;
    filter_type: object;
    conversion_time?: string;
    revenue_property?: string;
}

// Main CleverTap campaign interface
interface CleverTapCampaign {
    name: string;
    target_mode: 'email' | 'sms' | 'push' | 'whatsapp' | 'webpush';
    provider_nick_name?: string;
    provider_group_nickname?: string;
    content: any; // Use channel-specific content interfaces from notification.ts
    where?: CampaignWhere;
    to?: object; // For identity-based targeting
    when?: string | object; // 'now' or schedule object
    conversion_goal?: CampaignConversionGoal;
    send_to_all_devices?: boolean;
    estimate_only?: boolean;
    respect_frequency_caps?: boolean;
    system_control_group_include?: boolean;
    control_group?: object;
    skip_estimate?: boolean;
    users_limit_overall?: number;
    users_limit_per_run?: number;
    upper_cap_for_target_segment?: number;
    [key: string]: any;
}

export type {
    CleverTapCampaign,
    CampaignWhere,
    CampaignConversionGoal
}