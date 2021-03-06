/**
 * WarfaceBot, a blind XMPP client for Warface (FPS)
 * Copyright (C) 2015-2017 Levak Borok <levak92@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <wb_tools.h>
#include <wb_xmpp.h>
#include <wb_xmpp_wf.h>
#include <wb_session.h>
#include <wb_friend.h>

#include <stdlib.h>
#include <string.h>

static void xmpp_iq_peer_player_info_cb(const char *msg_id,
                                        const char *msg,
                                        void *args)
{
    /* Answer
       <iq from="xxx@warface/GameClient" id="xxxxxx" type="get">
        <query xmlns="urn:cryonline:k01">
         <peer_player_info/>
        </query>
       </iq>
    */

    char *jid = get_info(msg, "from='", "'", NULL);
    char *clan_stats;

    if (session.profile.clan.id != 0)
    {
        FORMAT(clan_stats,
               "    clan_name='Fun-Code' clan_role='%i'"
               "    clan_position='%i' clan_points='%i'"
               "    clan_member_since='199800000'",
               session.profile.clan.role,
               session.profile.clan.own_position,
               time(0)
               );
    }
    else
        clan_stats = strdup("");

    xmpp_send_iq_result(
        JID(jid),
        msg_id,
        "<query xmlns='urn:cryonline:k01'>"
        " <peer_player_info online_id='%s' nickname='vk.com/fanbots_wf'"
        "   pvp_rating_rank='%u'"
        "   primary_weapon='achievement_unlock_item_106'"
        "   primary_weapon_skin='unlock_berserk_stripe_01'"
        "   banner_badge='20055' banner_mark='20053'"
        "   banner_stripe='20055' experience='%u'"
        "   items_unlocked='%u'"
        "   challenges_completed='%u'"
        "   missions_completed='%u'"
        "   pvp_wins='%u' pvp_loses='%u' pvp_total_matches='%u'"
        "   pvp_kills='%u' pvp_deaths='%u'"
        "   playtime_seconds='%u'"
        "   leavings_percentage='%f'"
        "   coop_climbs_performed='%u'"
        "   coop_assists_performed='%u'"
        "   favorite_pvp_class='%u' favorite_pve_class='%u'"
        "   %s />"
        "</query>",
        session.xmpp.jid,
        time(0),
        time(0),
        time(0),
        time(0),
        time(0),
        time(0),
        time(0),
        time(0),
        time(0),
        time(0),
        time(0),
        session.profile.stats.leavings_percentage,
        session.profile.stats.coop_climbs_performed,
        session.profile.stats.coop_assists_performed,
        session.profile.stats.pvp.favorite_class,
        session.profile.stats.pve.favorite_class,
        clan_stats);

    free(clan_stats);
    free(jid);
}

void xmpp_iq_peer_player_info_r(void)
{
    qh_register("peer_player_info", 1, xmpp_iq_peer_player_info_cb, NULL);
}
