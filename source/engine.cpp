#include "engine.hpp"

void handle_ball_collision(Ball& b1, Ball& b2, float coef_resitution)
{
    // checks if the two balls are colliding with each other and returns if they are not
    Vec2 direction = Vec2::getVectorSubtraction(b2.pos, b1.pos);
    float distance = direction.getLength();

    if((distance == 0.0) || (distance > (b1.rad + b2.rad)))
    {
        return;
    }

    // if they are colliding, calculates the correction (how much to separate them)
    float correction = (b1.rad + b2.rad - distance) / 2.0f;

    // normalizes the direction to be just the direction, regardless of the size
    direction = direction.getNormalized();

    // calculates the new positions of the balls, adding to their vector the size of the 
    // correction in the direction of the direction vector (normalized before)
    Vec2 newpos_b1 = Vec2::getVectorScaled(direction, -correction);
    b1.pos.add(newpos_b1);

    // NOTE: when I forgot and left the sign of this correction negative, it worked
    // wrong but in a cool way kkkkkk so it might be something for the game in the future
    Vec2 newpos_b2 = Vec2::getVectorScaled(direction, correction);
    b2.pos.add(newpos_b2);

    // the dot product is basically how similar two vectors are. If the result is 1, they are the same.
    // if it is -1, they are completely opposite. So as I understand it, what is being calculated here
    // is how similar the current speed of the ball is to the direction of the impact between the two
    float v1 = b1.vel.dotProduct(direction);
    float v2 = b2.vel.dotProduct(direction);

    float m1 = b1.mass;
    float m2 = b2.mass;

    // calculates the new speeds after the collision, and applies them to the two balls
    float new_v1 = ((m1 * v1) + (m2 * v2) - ( m2 * (v1 - v2) * coef_resitution)) / (m1 + m2);
    float new_v2 = ((m1 * v1) + (m2 * v2) - ( m1 * (v2 - v1) * coef_resitution)) / (m1 + m2);

    Vec2 newvel_b1 = Vec2::getVectorScaled(direction, new_v1 - v1);
    b1.vel.add(newvel_b1);

    Vec2 newvel_b2 = Vec2::getVectorScaled(direction, new_v2 - v2);
    b2.vel.add(newvel_b2);
}

Vec2 get_closest_point_on_segment(Vec2 point, Vec2 seg_point_a, Vec2 seg_point_b)
{
    Vec2 seg = Vec2::getVectorSubtraction(seg_point_b, seg_point_a);
    float t = seg.dotProduct(seg);

    if (t == 0.0f)
    {
        return seg_point_a;
    }

    float calc = (point.dotProduct(seg) - seg_point_a.dotProduct(seg)) / t;
    t = fmax(0.0f, fmin(1.0f, calc));

    Vec2 closest_point = Vec2::getVectorScaled(seg, t);
    seg_point_a.add(closest_point);

    return seg_point_a;
}

void handle_bar_collision(Bar bar, Ball& bola)
{
    Vec2 closest_point = get_closest_point_on_segment(bola.pos, 
                                                      bar.start_point_meters, 
                                                      bar.end_point_meters);

    float rad = bar.radius_meters / 2.0f;

    Ball collision_ball(closest_point.x, 
                        closest_point.y, 
                        bar.speed_from_last_frame.x, 
                        bar.speed_from_last_frame.y, 
                        rad, 
                        bola.mass,
                        BLUE);

    // collision_ball.draw();
    handle_ball_collision(collision_ball, bola, 0.707f);
}

bool is_ball_inside_bucket(Ball ball, Bucket bucket)
{
    bool inside_bucket = true;
    Vec2 compare_point;

    compare_point = get_closest_point_on_segment(ball.pos, bucket.bar_left.start_point_meters, bucket.bar_left.end_point_meters);
    inside_bucket &= (ball.pos.x >= compare_point.x);
    if (!inside_bucket) return false;

    compare_point = get_closest_point_on_segment(ball.pos, bucket.bar_right.start_point_meters, bucket.bar_right.end_point_meters);
    inside_bucket &= (ball.pos.x <= compare_point.x);
    if (!inside_bucket) return false;

    compare_point = get_closest_point_on_segment(ball.pos, bucket.bar_left.start_point_meters, bucket.bar_right.end_point_meters);
    inside_bucket &= (ball.pos.y <= compare_point.y);
    if (!inside_bucket) return false;

    compare_point = get_closest_point_on_segment(ball.pos, bucket.bar_left.end_point_meters, bucket.bar_right.start_point_meters);
    inside_bucket &= (ball.pos.y >= compare_point.y);
    if (!inside_bucket) return false;

    return inside_bucket;
}


float map_pixel_to_meters_x(int pos_x)
{
    return (static_cast<float>(pos_x / SIM_SCALE));
}

float map_pixel_to_meters_y(int pos_y)
{
    // ugly, but works
    return ( - static_cast<float>((pos_y - SCREEN_HEIGHT) / SIM_SCALE));
}

int map_meters_to_pixel_x(float pos_x)
{
    return (static_cast<int>(pos_x * SIM_SCALE));
}

int map_meters_to_pixel_y(float pos_y)
{
    return (static_cast<int>(SCREEN_HEIGHT - (pos_y * SIM_SCALE)));
}

Vector2 map_point_to_pixel(Vec2 point)
{
    Vector2 ret;

    ret.x = static_cast<int>(point.x * SIM_SCALE);
    ret.y = static_cast<int>(SCREEN_HEIGHT - (point.y * SIM_SCALE));

    return ret;
}

float map_radius_to_pixel(float rad)
{
    return (rad * SIM_SCALE);
}